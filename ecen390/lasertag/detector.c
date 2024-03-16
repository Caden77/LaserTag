
#include "detector.h"
#include "buffer.h"
#include "filter.h"
#include "lockoutTimer.h"
#include "hitLedTimer.h"
#include "interrupts.h"

// Uncomment for debug prints
#define DEBUG
 
#if defined(DEBUG)
#include <stdio.h>
#include "xil_printf.h"
#define DPRINTF(...) printf(__VA_ARGS__)
#define DPCHAR(ch) outbyte(ch)
#else
#define DPRINTF(...)
#define DPCHAR(ch)
#endif

#define DETECTOR_NUM_PLAYERS 10
#define DETECTOR_MAX_POW_ELEMENT 9
#define DETECTOR_ADC_MAX 4095.0
#define DETECTOR_SCALED_RANGE 2.0

static uint32_t sample_cnt; // sample count

static bool hitDetectedFlag; // if hit is detected set to true
static bool ignoreAllHits; // true if ignore all hits

static bool freqIgnoredArray[DETECTOR_NUM_PLAYERS]; //array for ignored frequencies

static uint16_t maxPowerFilterNumber; // max power filter numbe4r
static uint16_t lastHitFrequencyNumber; // frequency number of last hit

static detector_hitCount_t playerHitArray[DETECTOR_NUM_PLAYERS]; // player hit array type

static uint16_t invocationCount; // invocation count

static uint16_t fudgeFactorArray[DETECTOR_NUM_PLAYERS]; // array for fudge factors
static uint16_t fudgeFactorIndex; // index for specific fudge factor element

// Initialize the detector module.
// By default, all frequencies are considered for hits.
// Assumes the filter module is initialized previously.
void detector_init(void) {
    sample_cnt = 0;
    hitDetectedFlag = false;
    //print(freqIgnoredArray);
    //freqIgnoredArray = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    //playerHitArray = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    maxPowerFilterNumber = 0;
    ignoreAllHits = false;
    invocationCount = 0;
    fudgeFactorArray[0] = 5;
    fudgeFactorArray[1] = 50;
    fudgeFactorArray[2] = 100;
    fudgeFactorArray[3] = 1000;
    fudgeFactorIndex = 3;
    lastHitFrequencyNumber = 0;
}

// helper function for insertion sorting current power values in ascending order
static void detector_sort(double arr[]) {
    uint16_t j, minIndex;
    for (uint16_t i = 0; i < DETECTOR_NUM_PLAYERS - 1; i++){
        minIndex = i;
        for (j = i + 1; j < DETECTOR_NUM_PLAYERS; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            double temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
        }
    }
    // for (uint16_t i = 1; i < DETECTOR_NUM_PLAYERS; i++) { //check if 0th element is largest
    //     double temp = arr[i];
    //     uint16_t j = i - 1;
    //     while (j >= 0 && arr[j] > temp) { //move element ahead if greater than temp
    //         arr[j + 1] = arr[j];
    //         j = j - 1;
    //     }
    //     arr[j + 1] = temp;
    // }
}

// freqArray is indexed by frequency number. If an element is set to true,
// the frequency will be ignored. Multiple frequencies can be ignored.
// Your shot frequency (based on the switches) is a good choice to ignore.
void detector_setIgnoredFrequencies(bool freqArray[]) {
    for (uint16_t i = 0; i < DETECTOR_NUM_PLAYERS; i++) {
        freqIgnoredArray[i] = freqArray[i];
    }
}

//helper function. Returns if there was a hit, given the powers of incoming signals
static bool detector_getIsHit() {
    //make an array with current power values (so we can reorganize them freely)
    double currPowVals[DETECTOR_NUM_PLAYERS];
    filter_getCurrentPowerValues(currPowVals);

    //sort in ascending order
    detector_sort(currPowVals);

    //get median
    double median = currPowVals[(DETECTOR_NUM_PLAYERS/2) - 1];
    //DPRINTF("median: %f\n", median);

    uint16_t fudgeFactor = fudgeFactorArray[fudgeFactorIndex];
    //DPRINTF("fudge: %d\n", fudgeFactor);
    //DPRINTF("fudgeFactorIndex: %d\n", fudgeFactorIndex);
    //DPRINTF("max pow element: %f\n", currPowVals[DETECTOR_MAX_POW_ELEMENT]);
    
    //if median val * fudgefactor < maxpower(currPowVals[9]), then hit is detected, else it is not
    if (currPowVals[DETECTOR_MAX_POW_ELEMENT] > (median * fudgeFactor)) {
        return true;
    }
    return false;
}

// helper function to set hitDetectedFlag flag to true if hit is detected
static void detector_hit_detect() {
    //if lockout timer not running
    if (!lockoutTimer_running()) {
        
        //run hit detection
        bool isHit = FALSE;
        if (!ignoreAllHits) {
            isHit = detector_getIsHit();
        }

        double currPowVals[DETECTOR_NUM_PLAYERS];
        filter_getCurrentPowerValues(currPowVals);

        uint16_t maxPowerFilterNum = 0;
        for (uint16_t i = 0; i < DETECTOR_NUM_PLAYERS; i++) {
            if (currPowVals[maxPowerFilterNum] < currPowVals[i]) {
                maxPowerFilterNum = i;
            }
        }

        //hit condition
        if (isHit && !freqIgnoredArray[maxPowerFilterNum]) {
            lockoutTimer_start();
            hitLedTimer_start();
                    
            //keep track of hits
            (playerHitArray[maxPowerFilterNum])++;
            lastHitFrequencyNumber = maxPowerFilterNum;

            hitDetectedFlag = TRUE;
        } else {
            hitDetectedFlag = FALSE;
        }
    } else {
        hitDetectedFlag = FALSE;
    }
}

//helper function: maps rawAdcValue to a double (-1.0 = 0, 1.0 = 4095, linearly)
// rawAdcValue: should be between 0 and 4095
static double mapAdcValueToDouble(buffer_data_t rawAdcValue) {
    return (DETECTOR_SCALED_RANGE/DETECTOR_ADC_MAX) * rawAdcValue - 1; // 2.0/4095.0 * rawAdcVal - 1
}



// Runs the entire detector: decimating FIR-filter, IIR-filters,
// power-computation, hit-detection. If interruptsCurrentlyEnabled = true,
// interrupts are running. If interruptsCurrentlyEnabled = false you can pop
// values from the ADC buffer without disabling interrupts. If
// interruptsCurrentlyEnabled = true, do the following:
// 1. disable interrupts.
// 2. pop the value from the ADC buffer.
// 3. re-enable interrupts.
// Ignore hits on frequencies specified with detector_setIgnoredFrequencies().
// Assumption: draining the ADC buffer occurs faster than it can fill.
void detector(bool interruptsCurrentlyEnabled) {
    //DPRINTF("inside detector\n");
    invocationCount++;
    
    uint32_t elementCount = buffer_elements();
    //DPRINTF("element count in buffer: %d\n", elementCount);
    for (uint32_t i = 0; i < elementCount; i++) {
        buffer_data_t rawAdcValue;
        if (interruptsCurrentlyEnabled) {
            // 1. disable interrupts.
            interrupts_disableArmInts();
        }
        // 2. pop the value from the ADC buffer.
        rawAdcValue = buffer_pop();
        if (interruptsCurrentlyEnabled) {
            // 3. re-enable interrupts.
            interrupts_enableArmInts();
        }

        //map rawAdcValue to a double (-1.0 = 0, 1.0 = 4095, linearly)
        double scaledAdcValue = mapAdcValueToDouble(rawAdcValue);

        filter_addNewInput(scaledAdcValue);
        sample_cnt++;
        if (sample_cnt >= FILTER_FIR_DECIMATION_FACTOR) {
            sample_cnt = 0; //clear current sample count

            //FIR Filter run
            filter_firFilter(); //output from xQueue goes to yQueue
            double filterPowers[FILTER_FIR_DECIMATION_FACTOR];

            maxPowerFilterNumber = 0;

            //run IIR filter for all 10
            for (uint16_t filterNumber = 0; filterNumber < FILTER_FREQUENCY_COUNT; filterNumber++) {
                filter_iirFilter(filterNumber);

                //run power computation for all 10 
                filterPowers[filterNumber] = filter_computePower(filterNumber, false, false);

                if (filterPowers[maxPowerFilterNumber] < filterPowers[filterNumber]) {
                    maxPowerFilterNumber = filterNumber;
                }
            }

            detector_hit_detect();
        }
    }
}

// Returns true if a hit was detected.
bool detector_hitDetected(void) {
    return hitDetectedFlag;
}

// Returns the frequency number that caused the hit.
uint16_t detector_getFrequencyNumberOfLastHit(void) {
    return lastHitFrequencyNumber;
}

// Clear the detected hit once you have accounted for it.
void detector_clearHit(void) {
    hitDetectedFlag = FALSE;
}

// Ignore all hits. Used to provide some limited invincibility in some game
// modes. The detector will ignore all hits if the flag is true, otherwise will
// respond to hits normally.
void detector_ignoreAllHits(bool flagValue) {
    ignoreAllHits = flagValue;
}

// Get the current hit counts.
// Copy the current hit counts into the user-provided hitArray
// using a for-loop.
void detector_getHitCounts(detector_hitCount_t hitArray[]) {
    for (uint16_t i = 0; i < DETECTOR_NUM_PLAYERS; i++) {
        hitArray[i] = playerHitArray[i];
    }
}

// Allows the fudge-factor index to be set externally from the detector.
// The actual values for fudge-factors is stored in an array found in detector.c
void detector_setFudgeFactorIndex(uint32_t factorIdx) {
    fudgeFactorIndex = factorIdx;
}

// Returns the detector invocation count.
// The count is incremented each time detector is called.
// Used for run-time statistics.
uint32_t detector_getInvocationCount(void) {
    return invocationCount;
}

/******************************************************
******************** Test Routines ********************
******************************************************/


static void detector_runSortTest(void) {
    //testing the sort algorithm
    double testArray[] = {44.0, 23.5, 45.0, 11.0, 9.0, 1.0, 4.0, 3.0, 9.0, 22.0};
    for (uint8_t i = 0; i < DETECTOR_NUM_PLAYERS; i++) {
        printf("%f\n", testArray[i]);
    }
    printf("\n");
    detector_sort(testArray);
    for (uint8_t i = 0; i < DETECTOR_NUM_PLAYERS; i++) {
        printf("%f\n", testArray[i]);
    }
    printf("\n");

    //testing the sort algorithm
    double testArray2[] = {40.0, 20.0, 150.0, 10.0, 15.0, 30.0, 35.0, 15.0, 25.0, 80.0};
    for (uint8_t i = 0; i < DETECTOR_NUM_PLAYERS; i++) {
        printf("%f\n", testArray2[i]);
    }
    printf("\n");
    detector_sort(testArray2);
    for (uint8_t i = 0; i < DETECTOR_NUM_PLAYERS; i++) {
        printf("%f\n", testArray2[i]);
    }
    printf("\n");

    //testing the sort algorithm
    double testArray3[] = {40.0, 20.0, 10.0, 150.0, 15.0, 30.0, 35.0, 15.0, 25.0, 80.0};
    for (uint8_t i = 0; i < DETECTOR_NUM_PLAYERS; i++) {
        printf("%f\n", testArray3[i]);
    }
    printf("\n");
    detector_sort(testArray3);
    for (uint8_t i = 0; i < DETECTOR_NUM_PLAYERS; i++) {
        printf("%f\n", testArray3[i]);
    }
    printf("\n");
}

// Students implement this as part of Milestone 3, Task 3.
// Create two sets of power values and call your hit detection algorithm
// on each set. With the same fudge factor, your hit detect algorithm
// should detect a hit on the first set and not detect a hit on the second.
void detector_runTest(void) {
    detector_init();

    //testing the sort algorithm
    detector_runSortTest();

    //set our fudge factor to 5
    detector_setFudgeFactorIndex(0);

    //fill the buffer with power values
    //test set 1 : expect hit detected
    filter_setCurrentPowerValue(0, 40);
    filter_setCurrentPowerValue(1, 20);
    filter_setCurrentPowerValue(2, 150);
    filter_setCurrentPowerValue(3, 10);
    filter_setCurrentPowerValue(4, 15);
    filter_setCurrentPowerValue(5, 30);
    filter_setCurrentPowerValue(6, 35);
    filter_setCurrentPowerValue(7, 15);
    filter_setCurrentPowerValue(8, 25);
    filter_setCurrentPowerValue(9, 80);

    detector_hit_detect();
    printf("hit Detected test 1: %d\n", detector_hitDetected());
    printf("\n");

    //fill the buffer with power values
    //test set 2 : expect hit detected
    filter_setCurrentPowerValue(0, 40);
    filter_setCurrentPowerValue(1, 20);
    filter_setCurrentPowerValue(2, 10);
    filter_setCurrentPowerValue(3, 150);
    filter_setCurrentPowerValue(4, 15);
    filter_setCurrentPowerValue(5, 30);
    filter_setCurrentPowerValue(6, 35);
    filter_setCurrentPowerValue(7, 15);
    filter_setCurrentPowerValue(8, 25);
    filter_setCurrentPowerValue(9, 80);

    detector_hit_detect();
    printf("hit Detected test 2: %d\n", detector_hitDetected());
    printf("frequency number of last hit: %d\n", detector_getFrequencyNumberOfLastHit());
    printf("\n");

    //test set 2 : expect no hit detected
    filter_setCurrentPowerValue(0, 10);
    filter_setCurrentPowerValue(1, 25);
    filter_setCurrentPowerValue(2, 30);
    filter_setCurrentPowerValue(3, 30);
    filter_setCurrentPowerValue(4, 45);
    filter_setCurrentPowerValue(5, 50);
    filter_setCurrentPowerValue(6, 55);
    filter_setCurrentPowerValue(7, 65);
    filter_setCurrentPowerValue(8, 70);
    filter_setCurrentPowerValue(9, 150);
    
    detector_hit_detect();
    printf("hit Detected test 2: %d\n", detector_hitDetected());
    printf("frequency number of last hit: %d\n", detector_getFrequencyNumberOfLastHit());

    printf("\n");
    printf("hit array: \n");
    detector_hitCount_t hitCounts[10];
    detector_getHitCounts(hitCounts);
    for (uint8_t i = 0; i < 10; i++) {
        printf("player %d: %d\n", i, hitCounts[i]);
    }
    printf("\n");
}
