
#include <stdbool.h>
#include <stdint.h>
#include "transmitter.h"
#include "mio.h"
#include "buttons.h"
#include "switches.h"
#include "utils.h"

#define TRANSMITTER_OUTPUT_PIN 13
#define TRANSMITTER_HIGH_VALUE 1
#define TRANSMITTER_LOW_VALUE 0
#define TRANSMITTER_RUNBOUND 20000 // 200ms
#define TRANSMITTER_ONESECOND 1000

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


#define TRANSMITTER_STATE_WAIT_MESSAGE "transmitter state: wait"
#define TRANSMITTER_STATE_LOW_MESSAGE "transmitter state: low"
#define TRANSMITTER_STATE_HIGH_MESSAGE "transmitter state: high"
#define TRANSMITTER_STATE_ERROR_MESSAGE "transmitter state: error"
// The transmitter state machine generates a square wave output at the chosen
// frequency as set by transmitter_setFrequencyNumber(). The step counts for the
// frequencies are provided in filter.h

// States for our trigger State Machine.
enum transmitter_st_t {
    wait_st, // wait for run signal
    low_st, // low state for our player signal
    high_st, // high state for our player signal
};

volatile static enum transmitter_st_t currentState;
volatile static enum transmitter_st_t prevState;
volatile static bool debugFirstRun;
volatile static uint16_t switchTimer; // timer for switching b/w 1,0
volatile static uint16_t burstTimer; // 200ms timer

volatile static uint16_t freqNumber;
volatile static bool isContinuousMode;
volatile static bool isFirstRun;
volatile static uint16_t storedFreqNum;

volatile static uint16_t playerbound;

void transmitter_debug() {
    if (debugFirstRun || prevState != currentState) {
        prevState = currentState;
        debugFirstRun = false;

        switch(currentState) {
            case wait_st:
                DPRINTF("%s\n", TRANSMITTER_STATE_WAIT_MESSAGE);
                break;
            case low_st:
                DPRINTF("%s\n", TRANSMITTER_STATE_LOW_MESSAGE);
                break;
            case high_st:
                DPRINTF("%s\n", TRANSMITTER_STATE_HIGH_MESSAGE);
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
    freqNumber = 0;
    currentState = wait_st;
    switchTimer = 0; //not needed
    debugFirstRun = true;
    isFirstRun = true;

    //debug stuff
    playerbound = 1000;
    storedFreqNum = 0;

    //setting pins
    mio_init(false);  // false disables any debug printing if there is a system failure during init.
    mio_setPinAsOutput(TRANSMITTER_OUTPUT_PIN);  // Configure the signal direction of the pin to be an output.
}

void transmitter_set_jf1(bool isOne) {
    if (isOne) {
        mio_writePin(TRANSMITTER_OUTPUT_PIN, TRANSMITTER_HIGH_VALUE); // Write a '1' to JF-1.
    } else {
        mio_writePin(TRANSMITTER_OUTPUT_PIN, TRANSMITTER_LOW_VALUE); // Write a '1' to JF-1.
    }
}

void updatePlayerBound(uint16_t storedFreqNum) {
    DPRINTF("updated player bound to: %d\n", storedFreqNum);
    playerbound = 1000; //TODO: change to actual num of ticks for the specific player
}

// Standard tick function.
void transmitter_tick() {
    transmitter_debug();

    //transitions
    switch(currentState) {
        case wait_st:
            if (isContinuousMode && !isFirstRun) {
                currentState = low_st;
            }
            break;
        case low_st: 
            if (burstTimer >= TRANSMITTER_RUNBOUND) {
                currentState = wait_st;
                switchTimer = 0;
                burstTimer = 0;
                if (!isContinuousMode) {
                    isFirstRun = true;
                }
            } 
            else if (switchTimer >= playerbound) { //FIXME: set playerbound
                switchTimer = 0;
                currentState = high_st;
            }
            break;
        case high_st:
            if (burstTimer >= TRANSMITTER_RUNBOUND) {
                currentState = wait_st;
                switchTimer = 0;
                burstTimer = 0;
                if (!isContinuousMode) {
                    isFirstRun = true;
                }
            }
            else if (switchTimer >= playerbound) {
                switchTimer = 0;
                currentState = low_st;
            } 
            break;
        default: //most likley an error
            break;
    }
    
    //actions
    switch(currentState) {
        case wait_st:
            if (storedFreqNum != freqNumber) {
                updatePlayerBound(storedFreqNum);
                freqNumber = storedFreqNum;
            }
            break;
        case low_st:
            switchTimer += 1;
            burstTimer += 1;
            transmitter_set_jf1(0);
            break;
        case high_st:
            switchTimer += 1;
            burstTimer += 1;
            transmitter_set_jf1(1);
            break;
        default: //most likley an error
            break;
    }
}

// Activate the transmitter.
void transmitter_run() {
    currentState = low_st;
    switchTimer = 0;
    burstTimer = 0;
    isFirstRun = false;
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
    if (currentState == wait_st) {
        isContinuousMode = continuousModeFlag;
        if (!isContinuousMode) {
            isFirstRun = true;
        }
    }
}

/******************************************************************************
***** Test Functions
******************************************************************************/

// Prints out the clock waveform to stdio. Terminates when BTN3 is pressed.
// Does not use interrupts, but calls the tick function in a loop.
void transmitter_runTest() {
    //while (!(buttons_read() & BUTTONS_BTN3_MASK)) {
    //    transmitter_tick();
    //}
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
    printf("inside noncontinuous test\n");
    while (!(buttons_read() & BUTTONS_BTN3_MASK)) {
        //DPRINTF("inside noncontinuous test while loop\n");
    }
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
    while (!(buttons_read() & BUTTONS_BTN3_MASK)) {
        transmitter_setFrequencyNumber(switches_read());
        utils_msDelay(TRANSMITTER_ONESECOND); // wait for 1 second
    }  
}
