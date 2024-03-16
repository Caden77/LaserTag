
#include "lockoutTimer.h"
#include "intervalTimer.h"
#include "isr.h"

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

// The lockoutTimer is active for 1/2 second once it is started.
// It is used to lock-out the detector once a hit has been detected.
// This ensures that only one hit is detected per 1/2-second interval.
#define LOCKOUT_BOUND_TICKS 50000 // (1/100,000) * 50,000 = 0.5sec

//debug print statements
#define LOCKOUT_STATE_WAIT_MESSAGE "Lockout: In state waiting."
#define LOCKOUT_STATE_RUNNING_MESSAGE "Lockout: In state running."
#define LOCKOUT_STATE_ERROR_MESSAGE "Lockout: In default error state."

// States for our lockoutTimer State Machine.
enum lockoutTimer_st_t {
    init_st, // initialize our state machine
    wait_st, // Wait until we get a start signal
    running_st, // increment tickCount until we reach 0.5sec
};
volatile static enum lockoutTimer_st_t currentState;
volatile static enum lockoutTimer_st_t prevState;

volatile static uint32_t tickCount;         //tracker for tick count
volatile static uint8_t debugFirstCall;     //debug
volatile static uint8_t isStarting;         //flag for starting


//Prints the state of the state machine, every time it changes
void debugLockoutTimer() {
    //if this is the first time called or the current state changes
    if (debugFirstCall || prevState != currentState) {
        //update our previous state and firstCall time
        prevState = currentState;
        debugFirstCall = 0;
        
        //Print out unique message for each state
        switch(currentState) {
            case wait_st:
                DPRINTF("%s\n", LOCKOUT_STATE_WAIT_MESSAGE);    //print message to track if we entered wait state
                break;
            case running_st:
                DPRINTF("%s\n", LOCKOUT_STATE_RUNNING_MESSAGE); //print message to track if we entered running state
                break;
            default:
                DPRINTF("%s\n", LOCKOUT_STATE_ERROR_MESSAGE);   //print message to track if we entered error state
                break;
        }
    }
}

// Perform any necessary inits for the lockout timer.
void lockoutTimer_init() {
    tickCount = 0;          //init tick counter
    debugFirstCall = 1;     //init debug first call
    isStarting = 0;         //init starting flag
    currentState = wait_st; //init current state to wait state
}

// Standard tick function.
void lockoutTimer_tick() {
    debugLockoutTimer();
    //transitions
    switch(currentState) {
            case wait_st:
                if (isStarting) {
                    currentState = running_st; //enter running_st
                    tickCount = 0; //reset tickcount
                }
                //else stay at wait state
                
                break;
            case running_st:
                if (tickCount >= LOCKOUT_BOUND_TICKS) {
                    currentState = wait_st; //enter wait_st
                    tickCount = 0; //reset tickout going to wait_st
                    isStarting = 0;
                }
                //else stay at running state
                
                break;
            default: // error if entered
                break;
    }
    
    //actions
    switch(currentState) {
            case wait_st:
                break;
            case running_st: //increment tickCount
                tickCount += 1;
                break;
            default: // error if entered
                break;
        }
}

// Calling this starts the timer.
void lockoutTimer_start() {
    isStarting = 1;
    //transition immediatley to running (don't wait for a tick)
    currentState = running_st;
    tickCount = 0; //reset tickcount
}

// Returns true if the timer is running.
bool lockoutTimer_running() {
    return currentState == running_st;
}

// Test function assumes interrupts have been completely enabled and
// lockoutTimer_tick() function is invoked by isr_function().
// Prints out pass/fail status and other info to console.
// Returns true if passes, false otherwise.
// This test uses the interval timer to determine correct delay for
// the interval timer.
bool lockoutTimer_runTest() {
    //start intervalTimer1
    intervalTimer_init(INTERVAL_TIMER_TIMER_1);
    intervalTimer_start(INTERVAL_TIMER_TIMER_1);
    //start lockout timer
    lockoutTimer_start();
    //wait while lockout timer is running
    //run
    while (lockoutTimer_running()) {
        //do nothing
    }
    DPRINTF("exited do while\n");
    //stop the interval timer when lockout timer stops
    intervalTimer_stop(INTERVAL_TIMER_TIMER_1);
    //print interval time
    DPRINTF("%f\n", intervalTimer_getTotalDurationInSeconds(INTERVAL_TIMER_TIMER_1));
}

