
#include "trigger.h"
#include "buttons.h"
#include "mio.h"
#include "intervalTimer.h"

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


#define TRIGGER_TIMEBOUND_TICKS 5000 //5000 ticks = 50ms
#define TRIGGER_GUN_TRIGGER_MIO_PIN 10
#define GUN_TRIGGER_PRESSED (true)

#define TRIGGER_START_SHOT_COUNT 10

volatile static uint32_t timer; //timer++ until 50 ms

// States for our trigger State Machine.
enum trigger_st_t {
    init_st, // initialize our state machine
    lowWait_st, // Wait until a trigger signal is detected
    highDebounce_st, // Start a timer to detect a debounced high signal tigger
    highWait_st, // Wait until the trigger signal is low
    lowDebounce_st // Stat a timer to detect a debounced low signal trigger
};

volatile static enum trigger_st_t currentState;
volatile static enum trigger_st_t prevState;
volatile static bool firstRun;
volatile static bool enabled;
volatile static trigger_shotsRemaining_t remainingShotCount;

volatile static bool triggerPressed();

void trigger_debug() {
    if (firstRun || prevState != currentState) {
        firstRun = false;
        prevState = currentState;

        switch (currentState) {
            case lowWait_st:
                DPRINTF("%s\n", TRIGGER_STATE_LOWWAIT_MESSAGE);
                break;
            case highDebounce_st:
                DPRINTF("%s\n", TRIGGER_STATE_HIGHDEBOUNCE_MESSAGE);
                break;
            case highWait_st:
                DPRINTF("%s\n", TRIGGER_STATE_HIGHWAIT_MESSAGE);
                break;
            case lowDebounce_st:
                DPRINTF("%s\n", TRIGGER_STATE_LOWDEBOUNCE_MESSAGE);
                break;
            default: //most likley an error
                DPRINTF("%s\n", TRIGGER_STATE_ERROR_MESSAGE);
                break;
        }
    }
}

// Init trigger data-structures.
// Initializes the mio subsystem.
// Determines whether the trigger switch of the gun is connected
// (see discussion in lab web pages).
void trigger_init() {
    enabled = true;
    firstRun = true;
    currentState = lowWait_st;

    mio_setPinAsInput(TRIGGER_GUN_TRIGGER_MIO_PIN); //initialize our mio pin
    //if (triggerPressed()) {
    //    enabled = false;
    //}
    remainingShotCount = TRIGGER_START_SHOT_COUNT;
}

// Standard tick function.
void trigger_tick() {
    //trigger_debug();

    bool trigger = triggerPressed();
    //DPRINTF("trigger: %d\n", trigger);

    //transition
    switch (currentState) {
        case lowWait_st:
            //printf("lowWait_st\n");
            if (trigger) {
                currentState = highDebounce_st;
                timer = 0;
            }
            else {
                currentState = lowWait_st;
            }
            break;
        case highDebounce_st:
            //DPRINTF("timer %d\n", timer);
            //printf("highDebounce_st\n");
            if (!trigger) {
                currentState = lowWait_st;
            } 
            else if (trigger && timer >= TRIGGER_TIMEBOUND_TICKS) {
                currentState = highWait_st;
                remainingShotCount -= 1; //-1 shot count
                if (remainingShotCount <= 0) {
                    enabled = false;
                }
            }
            else {
                currentState = highDebounce_st;
            }
            break;
        case highWait_st:
            //printf("highWait_st\n");
            if (!trigger){
                currentState = lowDebounce_st;
                timer = 0; // reset timer before going into lowDebounce
            }
            break;
        case lowDebounce_st:
            //printf("lowDebounce_st\n");
            if (!trigger && timer <= TRIGGER_TIMEBOUND_TICKS) {
                currentState = lowDebounce_st;
            }
            else if (!trigger && timer >= TRIGGER_TIMEBOUND_TICKS) {
                currentState = lowWait_st;
            }
            else if (trigger) {
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
            timer += 1;
            break;
        case highWait_st:
            break;
        case lowDebounce_st:
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
    while (!(buttons_read() & BUTTONS_BTN3_MASK)) {
        if (!enteredHigh && currentState == highWait_st) {
            enteredHigh = true;
            enteredLow = false;
            printf("D\n");
        }
        else if (!enteredLow && currentState == lowWait_st) {
            enteredLow = true;
            enteredHigh = false;
            printf("U\n");
        }
    }
}

volatile static bool triggerPressed() {
    return enabled & ((enabled & (mio_readPin(TRIGGER_GUN_TRIGGER_MIO_PIN) == GUN_TRIGGER_PRESSED)) || 
               (buttons_read() & BUTTONS_BTN0_MASK));
}