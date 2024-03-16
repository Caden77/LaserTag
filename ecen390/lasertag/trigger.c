
#include "trigger.h"
#include "buttons.h"
#include "mio.h"
#include "intervalTimer.h"
#include "transmitter.h"

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

// The trigger state machine debounces both the press and release of gun
// trigger. Ultimately, it will activate the transmitter when a debounced press
// is detected.

//state messages
#define TRIGGER_STATE_LOWWAIT_MESSAGE       "state: low wait"
#define TRIGGER_STATE_HIGHDEBOUNCE_MESSAGE  "state: high debounce"
#define TRIGGER_STATE_HIGHWAIT_MESSAGE      "state: high wait"
#define TRIGGER_STATE_LOWDEBOUNCE_MESSAGE   "state: low debounce"
#define TRIGGER_STATE_ERROR_MESSAGE         "!!!!!!!!Error State!!!!!!!!!"

//define the bound for a debounce, and the values for writing the pin
#define TRIGGER_TIMEBOUND_TICKS 5000 //5000 ticks = 50ms
#define TRIGGER_GUN_TRIGGER_MIO_PIN 10
#define GUN_TRIGGER_PRESSED (true)

//Define the number of shots the trigger can fire initially
#define TRIGGER_START_SHOT_COUNT 100

//For testing, indicates the delay needed for detecting a release on button 3
#define BOUNCE_DELAY 5

volatile static uint32_t timer; //timer++ until 50 ms

// States for our trigger State Machine.
enum trigger_st_t {
    init_st, // initialize our state machine
    lowWait_st, // Wait until a trigger signal is detected
    highDebounce_st, // Start a timer to detect a debounced high signal tigger
    highWait_st, // Wait until the trigger signal is low
    lowDebounce_st // Stat a timer to detect a debounced low signal trigger
};

//define the state
volatile static enum trigger_st_t currentState;
volatile static enum trigger_st_t prevState;

//flags for the state machine
volatile static bool firstRun;
volatile static bool enabled;
volatile static trigger_shotsRemaining_t remainingShotCount;

//function declarations (for those that need it)
volatile static bool triggerPressed();

//Used to debug the state machine by printing out the state that the state machine
//  transitions into.
void trigger_debug() {
    //If the state changes or it is the first run of the state machine
    if (firstRun || prevState != currentState) {
        //update variables for detecting state changes
        firstRun = false;
        prevState = currentState;

        //Print the message associated with the new state
        switch (currentState) {
            case lowWait_st:
                DPRINTF("%s\n", TRIGGER_STATE_LOWWAIT_MESSAGE); //debug print to track if we entered lowWait_st state
                break;
            case highDebounce_st:
                DPRINTF("%s\n", TRIGGER_STATE_HIGHDEBOUNCE_MESSAGE);//debug print to track if we entered highDebounce_st state
                break;
            case highWait_st:
                DPRINTF("%s\n", TRIGGER_STATE_HIGHWAIT_MESSAGE);//debug print to track if we entered highWait_st state
                break;
            case lowDebounce_st:
                DPRINTF("%s\n", TRIGGER_STATE_LOWDEBOUNCE_MESSAGE); //debug print to track if we entered lowDebounce_st state
                break;
            default: //most likley an error
                DPRINTF("%s\n", TRIGGER_STATE_ERROR_MESSAGE); //debug print for error
                break;
        }
    }
}

// Init trigger data-structures.
// Initializes the mio subsystem.
// Determines whether the trigger switch of the gun is connected
// (see discussion in lab web pages).
void trigger_init() {
    //initialize state machine flags
    enabled = true;
    firstRun = true;
    currentState = lowWait_st;

    //initialize mio pin
    mio_setPinAsInput(TRIGGER_GUN_TRIGGER_MIO_PIN); //initialize our mio pin
    if (triggerPressed()) {
        enabled = false;
    }
    //set the shot count
    remainingShotCount = TRIGGER_START_SHOT_COUNT;
}

// Standard tick function. Holds our state machine
void trigger_tick() {
    //trigger_debug(); //used to debug the state machine

    //get whether the trigger was pressed
    bool trigger = triggerPressed();

    //transitions
    switch (currentState) {
        case lowWait_st:
            //if pressed test for debounce
            if (trigger) {
                currentState = highDebounce_st;
                timer = 0;
            }
            else {
            //else wait
                currentState = lowWait_st;
            }
            break;
        case highDebounce_st:
            if (!trigger) {
                //detected bounce
                //go back to previous state
                currentState = lowWait_st;
            } 
            else if (trigger && timer >= TRIGGER_TIMEBOUND_TICKS) {
                //no bounce detected (for the full time limit)
                //update our state to high and signal a transmission.
                currentState = highWait_st;
                transmitter_run();

                //update shot count, and enabled if we reach zero
                remainingShotCount -= 1; //-1 shot count
                if (remainingShotCount <= 0) {
                    enabled = false;
                }
            }
            else {
                //wait for a potential bounce
                currentState = highDebounce_st;
            }
            break;
        case highWait_st:
            if (!trigger){
                //let go of trigger, go to low test bounce
                currentState = lowDebounce_st;
                timer = 0; // reset timer before going into lowDebounce
            }
            break;
        case lowDebounce_st:
            //state to test for a low bounce
            if (!trigger && timer <= TRIGGER_TIMEBOUND_TICKS) {
                //wait for a potential change of value on the trigger
                currentState = lowDebounce_st;
            }
            else if (!trigger && timer >= TRIGGER_TIMEBOUND_TICKS) {
                //no bounce detected in time limit, go to low state
                currentState = lowWait_st;
            }
            else if (trigger) {
                //detected bounce, go to previous state
                currentState = highWait_st;
            }
            break;
        default: //most likley an error
            break;
    }
    
    //actions
    switch (currentState) {
        case lowWait_st:
            break;
        case highDebounce_st:
            //increment timer while waiting for a bounce
            timer += 1;
            break;
        case highWait_st:
            break;
        case lowDebounce_st:
            //increment timer while waiting for a bounce
            timer += 1;
            break;
        default: //most likley an error
            break;
    }
}

// Enable the trigger state machine. The trigger state-machine is inactive until
// this function is called. This allows you to ignore the trigger when helpful
// (mostly useful for testing).
void trigger_enable() {
    enabled = true;
}

// Disable the trigger state machine so that trigger presses are ignored.
void trigger_disable() {
    enabled = false;
}

// Returns the number of remaining shots.
trigger_shotsRemaining_t trigger_getRemainingShotCount() {
    return remainingShotCount;
}

// Sets the number of remaining shots.
void trigger_setRemainingShotCount(trigger_shotsRemaining_t count) {
    remainingShotCount = count;
    if (count <= 0) {
        enabled = false;
    } else {
        enabled = true;
    }
}

// Runs the test continuously until BTN3 is pressed.
// The test just prints out a 'D' when the trigger or BTN0
// is pressed, and a 'U' when the trigger or BTN0 is released.
// Depends on the interrupt handler to call tick function.
void trigger_runTest() {
    bool enteredHigh = false;
    bool enteredLow = false;

    //While button 3 is not pressed
    while (!(buttons_read() & BUTTONS_BTN3_MASK)) {
        //if we recently arrived at highWait
        if (!enteredHigh && currentState == highWait_st) {
            //update that we arrived at high
            enteredHigh = true;
            enteredLow = false;
            //print that we arrived at highWait
            printf("D\n");
        }
        //if we recently arrived at lowWait
        else if (!enteredLow && currentState == lowWait_st) {
            //update that we arrived at low
            enteredLow = true;
            enteredHigh = false;
            //print that we arrived at lowWait
            printf("U\n");
        }
    }
    do {utils_msDelay(BOUNCE_DELAY);} while (buttons_read()); // for button release
}

//Detects a press of the trigger from the mio pin. Will not give a reading if the
//  enabled flag is false. This function may read from button 0 for testing or from the
//  gun trigger.
volatile static bool triggerPressed() {
    return enabled & ((enabled & (mio_readPin(TRIGGER_GUN_TRIGGER_MIO_PIN) == GUN_TRIGGER_PRESSED)) || 
               (buttons_read() & BUTTONS_BTN0_MASK));
}