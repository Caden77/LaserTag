
#include <stdbool.h>
#include <stdint.h>
#include "transmitter.h"
#include "mio.h"
#include "buttons.h"
#include "switches.h"
#include "utils.h"
#include "filter.h"

//Define pin values
#define TRANSMITTER_OUTPUT_PIN 13
#define TRANSMITTER_HIGH_VALUE 1
#define TRANSMITTER_LOW_VALUE 0

//Define how long the transmitter will transmit
#define TRANSMITTER_RUNBOUND 20000 // 200ms //bursttimer bound
#define TRANSMITTER_ONESECOND_CYCLES 100000 

// Uncomment for debug prints
//#define DEBUG
 
#if defined(DEBUG)
#include <stdio.h>
#include "xil_printf.h"
#define DPRINTF(...) printf(__VA_ARGS__)
#define DPCHAR(ch) outbyte(ch)
#else
#define DPRINTF(...)
#define DPCHAR(ch)
#endif

//debug messages for the state machine
#define TRANSMITTER_STATE_WAIT_MESSAGE "transmitter state: wait"
#define TRANSMITTER_STATE_LOW_MESSAGE "transmitter state: low"
#define TRANSMITTER_STATE_HIGH_MESSAGE "transmitter state: high"
#define TRANSMITTER_STATE_ERROR_MESSAGE "transmitter state: error"

// States for our trigger State Machine.
enum transmitter_st_t {
    wait_st, // wait for run signal
    low_st, // low state for our player signal
    high_st, // high state for our player signal
};

//define states
volatile static enum transmitter_st_t currentState;
volatile static enum transmitter_st_t prevState;

volatile static bool debugFirstRun;     //first run flag used by the debugger
volatile static uint16_t switchTimer; // timer for switching b/w 1,0
volatile static uint16_t burstTimer; // 200ms timer

volatile static uint16_t storedFreqNum;     //stores freqNum before it can be updated
volatile static uint16_t freqNumber;        //holds player, whos frequency will be output
volatile static bool isContinuousMode;      //bool to check continuous mode
volatile static bool prevIsContinuousMode;  //checks against itself 
volatile static bool isFirstRun;            //flag to check if it is first run

volatile static uint16_t playerbound;   //the timer bound between switching low/high state

// transmitter debugger w/ DPRINT
void transmitter_debug() {
    //check state status
    if (debugFirstRun || prevState != currentState) {
        prevState = currentState;
        debugFirstRun = false;

        DPRINTF("\n");

        //SM DPRINTs for which state we have entered for debugging
        switch(currentState) {
            case wait_st:   
                DPRINTF("%s\n", TRANSMITTER_STATE_WAIT_MESSAGE);    //wait_st
                break;
            case low_st:    
                DPRINTF("%s\n", TRANSMITTER_STATE_LOW_MESSAGE);     //low_st
                break;
            case high_st:
                DPRINTF("%s\n", TRANSMITTER_STATE_HIGH_MESSAGE);    //high_st
                break;
            default: //most likley an error
                DPRINTF("%s\n", TRANSMITTER_STATE_ERROR_MESSAGE);
                break;
        }
    }
}


// Standard init function.
void transmitter_init() {
    DPRINTF("Initialized transmitter\n");
    currentState = wait_st; //init to wait_st
    switchTimer = 0;
    debugFirstRun = true;   //for our debugger
    isFirstRun = true;      //set True because first run--used for continuous mode
    isContinuousMode = false;
    prevIsContinuousMode = isContinuousMode; //compare against itself

    //debug stuff
    storedFreqNum = 0;
    freqNumber = 0;
    playerbound = filter_frequencyTickTable[storedFreqNum] / 2; //from filter.h given filter freq count

    //setting pins
    mio_init(false);  // false disables any debug printing if there is a system failure during init.
    mio_setPinAsOutput(TRANSMITTER_OUTPUT_PIN);  // Configure the signal direction of the pin to be an output.
}

// helper function to set jf1
void transmitter_set_jf1(bool isOne) {
    if (isOne) {
        mio_writePin(TRANSMITTER_OUTPUT_PIN, TRANSMITTER_HIGH_VALUE); // Write a '1' to JF-1.
    } else {
        mio_writePin(TRANSMITTER_OUTPUT_PIN, TRANSMITTER_LOW_VALUE); // Write a '0' to JF-1.
    }
}

// updates player bound when called based on frequency number
void updatePlayerBound(uint16_t freqNum) {
    DPRINTF("updated player bound to: %d\n", freqNum);
    uint16_t playerFrequency = filter_frequencyTickTable[freqNum]; //table taken from filter.h
    playerbound = (uint16_t) (playerFrequency / 2); //set player bound, and /2 to account for switching between 0 and 1
}

// Standard tick function.
void transmitter_tick() {
    transmitter_debug();

    //transitions
    switch(currentState) {
        case wait_st:
            //if it is in continuous mode and it is not the first run
            if (isContinuousMode && !isFirstRun) { 
                currentState = low_st;
                transmitter_set_jf1(0); //set jf1 to 0 when in wait
            }
            break;
        case low_st: 
            //if our timer is > 20,000 ticks (200ms)
            if (burstTimer >= TRANSMITTER_RUNBOUND) {
                currentState = wait_st;
                switchTimer = 0;    //reset switchTimer before entering ns
                burstTimer = 0;     //reset burstTimer before entering ns
                transmitter_set_jf1(0);
                // if we are in continuous mode, and our prev value is not equal,
                if (isContinuousMode) { 
                    if (prevIsContinuousMode != isContinuousMode) {
                        isContinuousMode = false; // we get out of continuous mode
                    }
                }
                if (!isContinuousMode) { //have to be in first run if it is not cont. mode
                    isFirstRun = true;
                }
            } 
            //based on player freq, determines how long we stay in 0, 1 loops
            else if (switchTimer >= playerbound) { 
                switchTimer = 0;
                currentState = high_st; // switch to high_st
                transmitter_set_jf1(1); //don't forget to set jf1
            }
            break;
        case high_st:
            //if our timer is > 20,000 ticks (200ms)
            if (burstTimer >= TRANSMITTER_RUNBOUND) {
                currentState = wait_st;
                switchTimer = 0;    //reset switchTimer before entering ns
                burstTimer = 0;     //reset burstTimer before entering ns
                // if we are in continuous mode, and our prev value is not equal,
                if (isContinuousMode) {
                    if (prevIsContinuousMode != isContinuousMode) {
                        isContinuousMode = false; // we get out of continuous mode
                    }
                }
                transmitter_set_jf1(0);
                if (!isContinuousMode) {    //have to be in first run if it is not cont. mode
                    isFirstRun = true;
                }
            }
            //based on player freq, determines how long we stay in 0, 1 loops
            else if (switchTimer >= playerbound) {
                switchTimer = 0;
                currentState = low_st; // switch to low_st
                transmitter_set_jf1(0); //don't forget to set jf1
            } 
            break;
        default: //most likley an error
            break;
    }
    
    //actions
    switch(currentState) {
        case wait_st:
            //if we change the frequency on the switches
            if (storedFreqNum != freqNumber) {
                updatePlayerBound(storedFreqNum); // update the value to the switches
                freqNumber = storedFreqNum; // update
            }
            break;
        case low_st:
            DPRINTF("0"); //debug print used with transmitter_runTest()
            switchTimer += 1;   // switchTimer++ every cycle
            burstTimer += 1;    // burstTimer++ every cycle
            break;
        case high_st:
            DPRINTF("1");
            switchTimer += 1;   // switchTimer++ every cycle
            burstTimer += 1;    // burstTimer++ every cycle
            break;
        default: //most likley an error
            break;
    }
}

// Activate the transmitter.
void transmitter_run() {
    currentState = low_st;  //enter running transmitter therefore we go straight into low_st
    switchTimer = 0;        //reset switchTimer before enter low_st
    burstTimer = 0;         //reset burstTimer before entering low_st
    isFirstRun = false;     //won't be our first run.
    transmitter_set_jf1(0); 

    //update the frequency number if we just barley switched the frequency.
    if (storedFreqNum != freqNumber) {
        updatePlayerBound(storedFreqNum); // update the value to the switches
        freqNumber = storedFreqNum; // update
    }
}

// Returns true if the transmitter is still running.
bool transmitter_running() {
    return (currentState == low_st || currentState == high_st || (isContinuousMode && !isFirstRun));
}

// Sets the frequency number. If this function is called while the
// transmitter is running, the frequency will not be updated until the
// transmitter stops and transmitter_run() is called again.
void transmitter_setFrequencyNumber(uint16_t frequencyNumber) {
    storedFreqNum = frequencyNumber;
}

// Returns the current frequency setting.
uint16_t transmitter_getFrequencyNumber() {
    return freqNumber;
}

// Runs the transmitter continuously.
// if continuousModeFlag == true, transmitter runs continuously, otherwise, it
// transmits one burst and stops. To set continuous mode, you must invoke
// this function prior to calling transmitter_run(). If the transmitter is
// currently in continuous mode, it will stop running if this function is
// invoked with continuousModeFlag == false. It can stop immediately or wait
// until a 200 ms burst is complete. NOTE: while running continuously,
// the transmitter will only change frequencies in between 200 ms bursts.
void transmitter_setContinuousMode(bool continuousModeFlag) {
    //if in the state before we call run
    if (currentState == wait_st && continuousModeFlag) {
        prevIsContinuousMode = continuousModeFlag;
        isContinuousMode = continuousModeFlag; //checking continuousMode against itself to see if update is needed
    } else if (!continuousModeFlag) {
        prevIsContinuousMode = continuousModeFlag; //set our prev cont.mode flag = to current
    }
}

/******************************************************************************
***** Test Functions
******************************************************************************/
#define TRANSMITTER_TEST_TICK_PERIOD_IN_MS 10
#define BOUNCE_DELAY 5
#define TRANSMITTER_DEMONSTRATION_DELAY 400

// Prints out the clock waveform to stdio. Terminates when BTN3 is pressed.
// Does not use interrupts, but calls the tick function in a loop.
void transmitter_runTest() {
    DPRINTF("starting transmitter_runTest()\n");
    transmitter_init();                                         // init the transmitter.
    while (!(buttons_read() & BUTTONS_BTN3_MASK)) {             // Run continuously until BTN3 is pressed.
        uint16_t switchValue = switches_read() % FILTER_FREQUENCY_COUNT; // Compute a safe number from the switches.
        DPRINTF("switch values: %d\n", switchValue);    // set the frequency number based upon switch value.
        transmitter_setFrequencyNumber(switchValue);
        transmitter_run();                              // Start the transmitter.
        while(transmitter_running()) {                  // Keep ticking until it is done.
            transmitter_tick();                         // Tick
            utils_msDelay(TRANSMITTER_TEST_TICK_PERIOD_IN_MS);  //Delay a little between ticks
        }
        DPRINTF("completed one test period.\n");    //print to help debug
        DPRINTF("completed one burst\n");           //print to help debug
    }
    do {utils_msDelay(BOUNCE_DELAY);} while (buttons_read());   //release of button
    DPRINTF("exiting transmitter_runTest()\n");
}

// Tests the transmitter in non-continuous mode.
// The test runs until BTN3 is pressed.
// To perform the test, connect the oscilloscope probe
// to the transmitter and ground probes on the development board
// prior to running this test. You should see about a 300 ms dead
// spot between 200 ms pulses.
// Should change frequency in response to the slide switches.
// Depends on the interrupt handler to call tick function.
void transmitter_runTestNoncontinuous() {
    printf("starting transmitter_runTestNoncontinuous()\n");
    transmitter_init();                                         // init the transmitter.
    while (!(buttons_read() & BUTTONS_BTN3_MASK)) {             // Run continuously until BTN3 is pressed.
        uint16_t switchValue = switches_read() % FILTER_FREQUENCY_COUNT; //compute a safe number from the switches
        DPRINTF("switch values: %d\n", switchValue); // set the freq number based on switch value
        transmitter_setFrequencyNumber(switchValue); 
        transmitter_run();                              // start transmitter
        while(transmitter_running()) {                  // keep ticking until it is done
        }
        DPRINTF("completed one test period.\n");
        DPRINTF("completed one burst\n");
        utils_msDelay(TRANSMITTER_DEMONSTRATION_DELAY); //delay for a short amount of time
    }
    do {utils_msDelay(BOUNCE_DELAY);} while (buttons_read());   //release of button
    DPRINTF("exiting transmitter_runTestnonContinuous()\n");
}

// Tests the transmitter in continuous mode.
// To perform the test, connect the oscilloscope probe
// to the transmitter and ground probes on the development board
// prior to running this test.
// Transmitter should continuously generate the proper waveform
// at the transmitter-probe pin and change frequencies
// in response to changes in the slide switches.
// Test runs until BTN3 is pressed.
// Depends on the interrupt handler to call tick function.
void transmitter_runTestContinuous() {
    printf("starting transmitter_runTestContinuous()\n");
    transmitter_init();                                         // init the transmitter.
    transmitter_setContinuousMode(true);                        // set continuous mode to true
    transmitter_run();                                          // start transmitter
    while (!(buttons_read() & BUTTONS_BTN3_MASK)) {             //while button 3 is not pressed
        uint16_t switchValue = switches_read() % FILTER_FREQUENCY_COUNT; // compute a safe number from the switches
        DPRINTF("switch values: %d\n", switchValue);  //set the freq number based on switch value
        transmitter_setFrequencyNumber(switchValue);  
    }  
    do {utils_msDelay(BOUNCE_DELAY);} while (buttons_read());   //release of button
    transmitter_setContinuousMode(false); //turn off continuous mode after button is released
    DPRINTF("exiting transmitter_runTestnonContinuous()\n");
}
