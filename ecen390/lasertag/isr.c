
#include "isr.h"
#include "lockoutTimer.h"
#include "transmitter.h"
#include "trigger.h"
#include "hitLedTimer.h"
#include "buffer.h"
#include "interrupts.h"

// The interrupt service routine (ISR) is implemented here.
// Add function calls for state machine tick functions and
// other interrupt related modules.

// Perform initialization for interrupt and timing related modules.
void isr_init() {
    buffer_init();
    lockoutTimer_init();
    transmitter_init();
    trigger_init();
    hitLedTimer_init();
}

// This function is invoked by the timer interrupt at 100 kHz. (our tick function)
//  tick all initialized functions.
void isr_function() {
    lockoutTimer_tick();
    transmitter_tick();
    trigger_tick();
    hitLedTimer_tick();

    //grab data from ADC and store it in the ADC buffer at rate of 100kHz
    buffer_pushover(interrupts_getAdcData());
}