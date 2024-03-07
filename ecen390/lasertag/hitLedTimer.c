// The hitLedTimer is active for 1/2 second once it is started.
// While active, it turns on the LED connected to MIO pin 11
// and also LED LD0 on the ZYBO board.

//libraries for this file
#include "hitLedTimer.h"
#include "mio.h"
#include "leds.h"
#include "buttons.h"
#include "intervalTimer.h"
#include "isr.h"
#include "utils.h"

// Uncomment for debug prints
//#define DEBUG
 
//the following is for debug prints
#if defined(DEBUG)
#include <stdio.h>
#include "xil_printf.h"
#define DPRINTF(...) printf(__VA_ARGS__)
#define DPCHAR(ch) outbyte(ch)
#else
#define DPRINTF(...)
#define DPCHAR(ch)
#endif

//define pin values, including high and low values for the pin
#define HITLED_OUTPUT_PIN 11
#define HITLED_HIGH_VALUE 1
#define HITLED_LOW_VALUE 0

//define LED on/off values
#define HITLED_LD0_ON 1
#define HITLED_LD0_OFF 0

#define HITLED_BOUND_TICKS 50000 // (1/100,000) * 50,000 = 0.5sec

//define state machine messages for each state (including error state)
#define HITLED_STATE_WAIT_MESSAGE "In state waiting."
#define HITLED_STATE_RUNNING_MESSAGE "In state running."
#define HITLED_STATE_ERROR_MESSAGE "In default error state."

//For testing, declare the interval timer used to compare the timer
//  inside of this state machine
#define INTERVAL_TIMER_TIMER_1 1

//Used for testing, holds delay needed to test if btn3 is released
#define BOUNCE_DELAY 5



// States for our hitLedTimer State Machine.
enum hitLedTimer_st_t {
    init_st, // initialize our state machine
    wait_st, // Wait until we get a start signal
    running_st, // increment tickCount until we reach 0.5sec
};
//define our states
volatile static enum hitLedTimer_st_t currentState;
volatile static enum hitLedTimer_st_t prevState; //for debugging

volatile static uint32_t tickCount; //counter for the ledTimer
volatile static bool isEnabled; //flag to allow the start of the state machine
volatile static uint32_t btn3; //btn3's current value (1 for pressed, 0 for depressed)

volatile static uint8_t debugFirstCall; //first call flag for debugging

//define helper functions that are initialized below (that need it)
static void hitLedTimer_set_jf3(bool isOne);
static bool hitLedTimer_get_btn3_isPressed();

//Prints the state of the state machine, every time it changes
void hitLedTimer_debug() {
    //if this is the first time called or the current state changes
    if (debugFirstCall || prevState != currentState) {
        //update our previous state and firstCall time
        prevState = currentState;
        debugFirstCall = 0;
        
        //Print out unique message for each state
        switch(currentState) {
            case wait_st:
                DPRINTF("%s\n", HITLED_STATE_WAIT_MESSAGE); //debug print to track if we entered wait_st
                break;
            case running_st:
                DPRINTF("%s\n", HITLED_STATE_RUNNING_MESSAGE); //debug print to track if we entered running_st
                break;
            default:
                DPRINTF("%s\n", HITLED_STATE_ERROR_MESSAGE); //debug print for error
                break;
        }
    }
}


// Initializes values of the hitLedTimer.
void hitLedTimer_init() {
    //set the current state to wait, and reset the timer
    currentState = wait_st;
    tickCount = 0;
    isEnabled = true;

    //set the mio pin outputs
    mio_init(false);
    mio_setPinAsOutput(HITLED_OUTPUT_PIN);
}

// Standard tick function.
void hitLedTimer_tick() {

    hitLedTimer_debug(); //used to debug the state machine
    //transitions
    switch(currentState) {
            case wait_st:
                //wait at wait state until start is called
                
                break;
            case running_st:
                if (tickCount >= HITLED_BOUND_TICKS) {
                    //timer has ended
                    currentState = wait_st; //wait for next call
                    tickCount = 0; //reset tickout going to wait_st

                    //Mealy actions:
                    //turn the LED off
                    hitLedTimer_turnLedOff();
                }
                //else stay at running state
                
                break;
            default:
                break;
    }
    
    //actions
    switch(currentState) {
            case wait_st:
                break;
            case running_st: //increment tickCount
                tickCount += 1;
                break;
            default:
                break;
        }
}

// Calling this starts the timer. Holds transition logic
//  from the wait state to the running state to start
//  the state machine
void hitLedTimer_start() {
    if (isEnabled && (currentState == wait_st)) {
        //if we are not running yet and we can (because of enabled)

        currentState = running_st; //run the timer
        tickCount = 0; //reset tickcount

        //turn LED on
        hitLedTimer_turnLedOn();
    }
}

// Returns true if the timer is currently running.
bool hitLedTimer_running() {
    return (currentState == running_st);
}

// Turns the gun's hit-LED on.
void hitLedTimer_turnLedOn() {
    leds_write(HITLED_LD0_ON);
    hitLedTimer_set_jf3(true);
}

// Turns the gun's hit-LED off.
void hitLedTimer_turnLedOff() {
    leds_write(HITLED_LD0_OFF);
    hitLedTimer_set_jf3(false);
}

// Disables the hitLedTimer.
void hitLedTimer_disable() {
    isEnabled = false;
}

// Enables the hitLedTimer.
void hitLedTimer_enable() {
    isEnabled = true;
}

// Runs a visual test of the hit LED until BTN3 is pressed.
// The test continuously blinks the hit-led on and off.
// Depends on the interrupt handler to call tick function.
void hitLedTimer_runTest() {
    DPRINTF("inside hitLedTimer test\n");
    intervalTimer_init(INTERVAL_TIMER_TIMER_1);

    //run until btn3 is pressed
    while (true) {
        //reset the working interval timer
        intervalTimer_reset(INTERVAL_TIMER_TIMER_1);
        intervalTimer_start(INTERVAL_TIMER_TIMER_1);
        //start our own timer
        hitLedTimer_start();
        while (hitLedTimer_running()) {
            //do nothing while the state machine runs
        }
        //exited (our timer stopped), stop the working timer
        intervalTimer_stop(INTERVAL_TIMER_TIMER_1);
        //print how long our timer ran for
        DPRINTF("%f\n", intervalTimer_getTotalDurationInSeconds(INTERVAL_TIMER_TIMER_1));

        utils_msDelay(300);
        
        //break out of while loop if btn3 is pressed
        if (hitLedTimer_get_btn3_isPressed()) {
            break;
        }
    }
    do {utils_msDelay(BOUNCE_DELAY);} while (buttons_read());
}

//Set pin 3 to the value of isOne. Is a helpper function.
static void hitLedTimer_set_jf3(bool isOne) {
    if (isOne) {
        mio_writePin(HITLED_OUTPUT_PIN, HITLED_HIGH_VALUE);
    } else {
        mio_writePin(HITLED_OUTPUT_PIN, HITLED_LOW_VALUE);
    }
}

// helper function checking if BTN3 is pressed
static bool hitLedTimer_get_btn3_isPressed() {
    return (buttons_read() & BUTTONS_BTN3_MASK);
}