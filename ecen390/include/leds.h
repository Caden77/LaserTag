/*
This software is provided for student assignment use in the Department of
Electrical and Computer Engineering, Brigham Young University, Utah, USA.

Users agree to not re-host, or redistribute the software, in source or binary
form, to other persons or other institutions. Users may modify and use the
source code for personal or educational use.

For questions, contact Brad Hutchings or Jeff Goeders, https://ece.byu.edu/
*/

#ifndef LEDS_H_
#define LEDS_H_

#include <stdbool.h>
#include <stdint.h>

// This will init the GPIO hardware so you can write to the 4 LEDs  (LD3 - LD0)
// on the ZYBO board. if printFailedStatusFlag = 1, it will print out an error
// message if an internal error occurs.
int32_t leds_init(bool printFailedStatusFlag);

// This write the lower 4 bits of ledValue to the LEDs.
// LED3 gets bit3 and so forth.
// '1' = illuminated.
// '0' = off.
void leds_write(int32_t ledValue);

// These control the LED LD4 attached to MIO 7 on the ZYBO board.
void leds_writeLd4(int32_t ledValue);

// This blinks all of the LEDs for several seconds to provide a visual test of
// the code.
int32_t leds_runTest();

#endif /* LEDS_H_ */
