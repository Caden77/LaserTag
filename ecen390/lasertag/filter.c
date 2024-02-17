/*
This software is provided for student assignment use in the Department of
Electrical and Computer Engineering, Brigham Young University, Utah, USA.
Users agree to not re-host, or redistribute the software, in source or binary
form, to other persons or other institutions. Users may modify and use the
source code for personal or educational use.
For questions, contact Brad Hutchings or Jeff Goeders, https://ece.byu.edu/
*/

#include "filter.h"

// Filtering routines for the laser-tag project.
// Filtering is performed by a two-stage filter, as described below.

// 1. First filter is a decimating FIR filter with a configurable number of taps
// and decimation factor.
// 2. The output from the decimating FIR filter is passed through a bank of 10
// IIR filters. The characteristics of the IIR filter are fixed.

/****************************************
 * Global Variables
 * ***********************************************/

#define FILTER_IIR_FILTER_COUNT 10
#define Z_QUEUE_SIZE (IIR_B_COEFFICIENT_COUNT)
#define X_QUEUE_SIZE (FIR_FILTER_B_COEFFICIENT_COUNT) //Input size
#define Y_QUEUE_SIZE (IIR_B_COEFFICIENT_COUNT)
#define OUTPUT_QUEUES_SIZE 2000
#define QUEUE_INIT_VALUE 0
#define ZERO 0

static queue_t xQueue; //incoming input
static queue_t yQueue; //history of FIR outputs
static queue_t zQueue[FILTER_IIR_FILTER_COUNT]; //history of IIR outputs (for each player filter)
static queue_t outputQueues[FILTER_IIR_FILTER_COUNT]; //power computation

static double prevPower[FILTER_IIR_FILTER_COUNT]; //stores the previously computed powers
static queue_data_t oldestPowerValues[FILTER_IIR_FILTER_COUNT]; //stores the oldest power values



/******************************************************************************
***** Main Filter Functions
******************************************************************************/

//helper function for initializing ZQueues for filter_init()
static void initZQueues() {
    //go through each IIR filter
    for (uint32_t i = 0; i < FILTER_IIR_FILTER_COUNT; i++) {
        //initialize a queue for the filter
        queue_init(&(zQueue[i]), Z_QUEUE_SIZE, "zQueue"); //rename as zQueue
        for (uint32_t j = 0; j < Z_QUEUE_SIZE; j++) {
            queue_overwritePush(&(zQueue[i]), QUEUE_INIT_VALUE); //pushes onto queue, if full, pops, then pushes
        }
    }
}

//helper function for initializing XQueues for filter_init()
static void initXQueue() {
    //initialize the one xqueue
    queue_init(&xQueue, X_QUEUE_SIZE, "xQueue"); //rename as xQueue
    for (uint32_t j = 0; j < X_QUEUE_SIZE; j++) {
        queue_overwritePush(&xQueue, QUEUE_INIT_VALUE); //pushes onto queue, if full, pops, then pushes
    }
}

//helper function for initializing YQueues for filter_init()
static void initYQueue() {
    //initialize the one yqueue
    queue_init(&yQueue, Y_QUEUE_SIZE, "yQueue"); //rename as yQueue
    for (uint32_t j = 0; j < Y_QUEUE_SIZE; j++) {
        queue_overwritePush(&yQueue, QUEUE_INIT_VALUE); //pushes onto queue, if full, pops, then pushes
    }
}

//helper function for initializing OutputQueues for filter_init()
static void initOutputQueues() {
    //go through all IIR filters
    for (uint32_t i = 0; i < FILTER_IIR_FILTER_COUNT; i++) {
        //initialize an outputqueue per IIR filter
        queue_init(&(outputQueues[i]), OUTPUT_QUEUES_SIZE, "outputQueue"); //rename as outputQueue
        for (uint32_t j = 0; j < OUTPUT_QUEUES_SIZE; j++) {
            queue_overwritePush(&(outputQueues[i]), QUEUE_INIT_VALUE); //pushes onto queue, if full, pops, then pushes
        }
    }
}


// Must call this prior to using any filter functions.
void filter_init() {
  // Init queues and fill them with 0s.
  initXQueue();  // Call queue_init() on xQueue and fill it with zeros.
  initYQueue();  // Call queue_init() on yQueue and fill it with zeros.
  initZQueues(); // Call queue_init() on all of the zQueues and fill each z queue with zeros.
  initOutputQueues();  // Call queue_init() on all of the outputQueues and fill each outputQueue with zeros.
}

// Use this to copy an input into the input queue of the FIR-filter (xQueue).
void filter_addNewInput(double x) {
    queue_overwritePush(&xQueue, x);
}

// Invokes the FIR-filter. Input is contents of xQueue.
// Output is returned and is also pushed on to yQueue.
double filter_firFilter() {
    double ySum = 0;
    //for each B coefficient in our FIR filter
    for (uint16_t i = 0; i < FIR_FILTER_B_COEFFICIENT_COUNT; i++) {
        //ysum = ysum _ xqueue at i * fircoefcount - i - 1
        ySum += queue_readElementAt(&xQueue, i) * firCoefficients[FIR_FILTER_B_COEFFICIENT_COUNT - i - 1];
    }

    queue_overwritePush(&yQueue, ySum);
}

// Use this to invoke a single iir filter. Input comes from yQueue.
// Output is returned and is also pushed onto zQueue[filterNumber].
double filter_iirFilter(uint16_t filterNumber) {
    double bSum = 0;
    //for each b coefficient for the band pass filter
    for (uint16_t k = 0; k < IIR_B_COEFFICIENT_COUNT; k++) {
        //multiply the yQueue input by the b coefficient as a weighted sum
        bSum += filter_getIirBCoefficientArray(filterNumber)[k] *
                 queue_readElementAt(&yQueue, Y_QUEUE_SIZE - k - 1);
    }

    double aSum = 0;
    //for each A coefficient in our filter
    for (uint16_t k = 0; k < IIR_A_COEFFICIENT_COUNT - 1; k++) {
        //multiply the previous outputs by the a coefficient as a weighted sum
        aSum += filter_getIirACoefficientArray(filterNumber)[k] * 
                 queue_readElementAt(&zQueue[filterNumber], Z_QUEUE_SIZE - k - 1);
    }

    //add the weighted sums and push onto our output/z queues
    double sum = (bSum - aSum);
    queue_overwritePush(&zQueue[filterNumber], sum);
    queue_overwritePush(&outputQueues[filterNumber], sum);
}

// Use this to compute the power for values contained in an outputQueue.
// If force == true, then recompute power by using all values in the
// outputQueue. This option is necessary so that you can correctly compute power
// values the first time. After that, you can incrementally compute power values
// by:
// 1. Keeping track of the power computed in a previous run, call this
// prev-power.
// 2. Keeping track of the oldest outputQueue value used in a previous run, call
// this oldest-value.
// 3. Get the newest value from the power queue, call this newest-value.
// 4. Compute new power as: prev-power - (oldest-value * oldest-value) +
// (newest-value * newest-value). Note that this function will probably need an
// array to keep track of these values for each of the 10 output queues.
double filter_computePower(uint16_t filterNumber, bool forceComputeFromScratch,
                           bool debugPrint) {
    // init outputQueue
    queue_t* outputQueue = filter_getIirOutputQueue(filterNumber);
    double power = 0.0; //Set power to 0
    if (forceComputeFromScratch) {
        // go through each queue and compute pow vals for the first time.
        for (uint32_t i = 0; i < OUTPUT_QUEUES_SIZE; i++) {
            queue_data_t element = queue_readElementAt(outputQueue, i);
            power += (element * element);
        }
    }
    //go into else whenever it is not the first time computing power
    else {
        queue_data_t newValue = queue_readElementAt(outputQueue, OUTPUT_QUEUES_SIZE - 1);
        // Compute new power as: prev-power - (oldest-value * oldest-value) +
        // (newest-value * newest-value).
        power = prevPower[filterNumber] - (oldestPowerValues[filterNumber] * oldestPowerValues[filterNumber]) + (newValue * newValue);
    }
    prevPower[filterNumber] = power; //sets previous power equal to current power
    oldestPowerValues[filterNumber] = queue_readElementAt(outputQueue, ZERO);
    return power;
}

// Returns the last-computed output power value for the IIR filter
// [filterNumber].
double filter_getCurrentPowerValue(uint16_t filterNumber) {
    return prevPower[filterNumber];
}

// Sets a current power value for a specific filter number.
// Useful in testing the detector.
void filter_setCurrentPowerValue(uint16_t filterNumber, double value) {
    prevPower[filterNumber] = value;
}

// Get a copy of the current power values.
// This function copies the already computed values into a previously-declared
// array so that they can be accessed from outside the filter software by the
// detector. Remember that when you pass an array into a C function, changes to
// the array within that function are reflected in the returned array.
void filter_getCurrentPowerValues(double powerValues[]) {
    for (uint32_t i = 0; i < FILTER_IIR_FILTER_COUNT; i++) {
        //for each value, copy the value into powerValues at the same index
        powerValues[i] = prevPower[i];
    }
}

// Using the previously-computed power values that are currently stored in
// currentPowerValue[] array, copy these values into the normalizedArray[]
// argument and then normalize them by dividing all of the values in
// normalizedArray by the maximum power value contained in currentPowerValue[].
// The pointer argument indexOfMaxValue is used to return the index of the
// maximum value. If the maximum power is zero, make sure to not divide by zero
// and that *indexOfMaxValue is initialized to a sane value (like zero).
void filter_getNormalizedPowerValues(double normalizedArray[],
                                     uint16_t *indexOfMaxValue) {
    uint32_t maxPower = 0;
    //compute max power by going through each power for each filter
    for (uint32_t i = 0; i < FILTER_IIR_FILTER_COUNT; i++) {
        if (maxPower < prevPower[i]) {
            //update max power and its index
            maxPower = prevPower[i];
            *indexOfMaxValue = i; 
        }
    }

    //populate the normalized array for each IIR filter
    for (uint32_t i = 0; i < FILTER_IIR_FILTER_COUNT; i++) {
        normalizedArray[i] = prevPower[i] / maxPower;
    }
}

/******************************************************************************
***** Verification-Assisting Functions
***** External test functions access the internal data structures of filter.c
***** via these functions. They are not used by the main filter functions.
******************************************************************************/

// Returns the array of FIR coefficients.
const double *filter_getFirCoefficientArray() {
    return firCoefficients;
}

// Returns the number of FIR coefficients.
uint32_t filter_getFirCoefficientCount() {
    return FIR_FILTER_B_COEFFICIENT_COUNT;
}

// Returns the array of coefficients for a particular filter number.
const double *filter_getIirACoefficientArray(uint16_t filterNumber) {
    return iirACoefficientConstants[filterNumber];
}

// Returns the number of A coefficients.
uint32_t filter_getIirACoefficientCount() {
    return IIR_A_COEFFICIENT_COUNT;
}

// Returns the array of coefficients for a particular filter number.
const double *filter_getIirBCoefficientArray(uint16_t filterNumber) {
    return iirBCoefficientConstants[filterNumber];
}

// Returns the number of B coefficients.
uint32_t filter_getIirBCoefficientCount() {
    return IIR_B_COEFFICIENT_COUNT;
}

// Returns the size of the yQueue.
uint32_t filter_getYQueueSize() {
    return IIR_B_COEFFICIENT_COUNT;
}

// Returns the decimation value. (TODO)
uint16_t filter_getDecimationValue() {
    return 10;
}

// Returns the address of xQueue.
queue_t *filter_getXQueue() {
    return &xQueue;
}

// Returns the address of yQueue.
queue_t *filter_getYQueue() {
    return &yQueue;
}

// Returns the address of zQueue for a specific filter number.
queue_t *filter_getZQueue(uint16_t filterNumber) {
    return &zQueue[filterNumber];
}

// Returns the address of the IIR output-queue for a specific filter-number.
queue_t *filter_getIirOutputQueue(uint16_t filterNumber) {
    return &outputQueues[filterNumber];
}