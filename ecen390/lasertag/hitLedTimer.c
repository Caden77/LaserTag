// The hitLedTimer is active for 1/2 second once it is started.
// While active, it turns on the LED connected to MIO pin 11
// and also LED LD0 on the ZYBO board.

#include "hitLedTimer.h"
#include "mio.h"
#include "leds.h"
#include "buttons.h"
#include "intervalTimer.h"
#include "isr.h"
#include "utils.h"

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


#define HITLED_OUTPUT_PIN 11
#define HITLED_HIGH_VALUE 1
#define HITLED_LOW_VALUE 0
#define HITLED_LD0_ON 1
#define HITLED_LD0_OFF 0

#define HITLED_BOUND_TICKS 50000 // (1/100,000) * 50,000 = 0.5sec

#define HITLED_STATE_WAIT_MESSAGE "In state waiting."
#define HITLED_STATE_RUNNING_MESSAGE "In state running."
#define HITLED_STATE_ERROR_MESSAGE "In default error state."

#define INTERVAL_TIMER_TIMER_1 1



// States for our hitLedTimer State Machine.
enum hitLedTimer_st_t {
    init_st, // initialize our state machine
    wait_st, // Wait until we get a start signal
    running_st, // increment tickCount until we reach 0.5sec
};
volatile static enum hitLedTimer_st_t currentState;
volatile static enum hitLedTimer_st_t prevState;

volatile static uint32_t tickCount;
volatile static uint8_t debugFirstCall;
volatile static bool isEnabled;
volatile static uint32_t btn3;

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
                DPRINTF("%s\n", HITLED_STATE_WAIT_MESSAGE);
                break;
            case running_st:
                DPRINTF("%s\n", HITLED_STATE_RUNNING_MESSAGE);
                break;
            default:
                DPRINTF("%s\n", HITLED_STATE_ERROR_MESSAGE);
                break;
        }
    }
}


// Need to init things.
void hitLedTimer_init() {
    currentState = wait_st;
    tickCount = 0;
    isEnabled = true;

    mio_init(false);
    mio_setPinAsOutput(HITLED_OUTPUT_PIN);
}

// Standard tick function.
void hitLedTimer_tick() {

    hitLedTimer_debug();
    //transitions
    switch(currentState) {
            case wait_st:
                //wait at wait state until start is called
                
                break;
            case running_st:
                if (tickCount >= HITLED_BOUND_TICKS) {
                    currentState = wait_st;
                    tickCount = 0; //reset tickout going to wait_st
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

// Calling this starts the timer.
void hitLedTimer_start() {
    if (isEnabled && (currentState == wait_st)) {
        currentState = running_st;
        tickCount = 0; //reset tickcount
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
    while (true) {
        intervalTimer_reset(INTERVAL_TIMER_TIMER_1);
        intervalTimer_start(INTERVAL_TIMER_TIMER_1);
        hitLedTimer_start();
        while (hitLedTimer_running()) {
            //do nothing
        }
        intervalTimer_stop(INTERVAL_TIMER_TIMER_1);
        DPRINTF("%f\n", intervalTimer_getTotalDurationInSeconds(INTERVAL_TIMER_TIMER_1));

        utils_msDelay(50);
        
        if (hitLedTimer_get_btn3_isPressed()) {
            break;
        }
    }
}

static void hitLedTimer_set_jf3(bool isOne) {
    if (isOne) {
        mio_writePin(HITLED_OUTPUT_PIN, HITLED_HIGH_VALUE);
    } else {
        mio_writePin(HITLED_OUTPUT_PIN, HITLED_LOW_VALUE);
    }
}

static bool hitLedTimer_get_btn3_isPressed() {
    return (buttons_read() & BUTTONS_BTN3_MASK);
}