/*
This software is provided for student assignment use in the Department of
Electrical and Computer Engineering, Brigham Young University, Utah, USA.
Users agree to not re-host, or redistribute the software, in source or binary
form, to other persons or other institutions. Users may modify and use the
source code for personal or educational use.
For questions, contact Brad Hutchings or Jeff Goeders, https://ece.byu.edu/
*/

#ifndef FILTER_H_
#define FILTER_H_

#include <stdint.h>

#include "queue.h"

#define IIR_B_COEFFICIENT_COUNT 11
#define IIR_A_COEFFICIENT_COUNT 11
#define FIR_FILTER_B_COEFFICIENT_COUNT 81


#define FILTER_SAMPLE_FREQUENCY_IN_KHZ 100
#define FILTER_FREQUENCY_COUNT 10
#define FILTER_FIR_DECIMATION_FACTOR                                           \
  10 // FIR-filter needs this many new inputs to compute a new output.
#define FILTER_INPUT_PULSE_WIDTH                                               \
  2000 // This is the width of the pulse you are looking for, in terms of
       // decimated sample count.
// These are the tick counts that are used to generate the user frequencies.
// Not used in filter.h but are used to TEST the filter code.
// Placed here for general access as they are essentially constant throughout
// the code. The transmitter will also use these.
static const uint16_t filter_frequencyTickTable[FILTER_FREQUENCY_COUNT] = {
    68, 58, 50, 44, 38, 34, 30, 28, 26, 24};

// Filtering routines for the laser-tag project.
// Filtering is performed by a two-stage filter, as described below.

// 1. First filter is a decimating FIR filter with a configurable number of taps
// and decimation factor.
// 2. The output from the decimating FIR filter is passed through a bank of 10
// IIR filters. The characteristics of the IIR filter are fixed.

/******************************************************************************
***** Main Filter Functions
******************************************************************************/

// Must call this prior to using any filter functions.
void filter_init();

// Use this to copy an input into the input queue of the FIR-filter (xQueue).
void filter_addNewInput(double x);

// Invokes the FIR-filter. Input is contents of xQueue.
// Output is returned and is also pushed on to yQueue.
double filter_firFilter();

// Use this to invoke a single iir filter. Input comes from yQueue.
// Output is returned and is also pushed onto zQueue[filterNumber].
double filter_iirFilter(uint16_t filterNumber);

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
                           bool debugPrint);

// Returns the last-computed output power value for the IIR filter
// [filterNumber].
double filter_getCurrentPowerValue(uint16_t filterNumber);

// Sets a current power value for a specific filter number.
// Useful in testing the detector.
void filter_setCurrentPowerValue(uint16_t filterNumber, double value);

// Get a copy of the current power values.
// This function copies the already computed values into a previously-declared
// array so that they can be accessed from outside the filter software by the
// detector. Remember that when you pass an array into a C function, changes to
// the array within that function are reflected in the returned array.
void filter_getCurrentPowerValues(double powerValues[]);

// Using the previously-computed power values that are currently stored in
// currentPowerValue[] array, copy these values into the normalizedArray[]
// argument and then normalize them by dividing all of the values in
// normalizedArray by the maximum power value contained in currentPowerValue[].
// The pointer argument indexOfMaxValue is used to return the index of the
// maximum value. If the maximum power is zero, make sure to not divide by zero
// and that *indexOfMaxValue is initialized to a sane value (like zero).
void filter_getNormalizedPowerValues(double normalizedArray[],
                                     uint16_t *indexOfMaxValue);

/******************************************************************************
***** Verification-Assisting Functions
***** External test functions access the internal data structures of filter.c
***** via these functions. They are not used by the main filter functions.
******************************************************************************/

// Returns the array of FIR coefficients.
const double *filter_getFirCoefficientArray();

// Returns the number of FIR coefficients.
uint32_t filter_getFirCoefficientCount();

// Returns the array of coefficients for a particular filter number.
const double *filter_getIirACoefficientArray(uint16_t filterNumber);

// Returns the number of A coefficients.
uint32_t filter_getIirACoefficientCount();

// Returns the array of coefficients for a particular filter number.
const double *filter_getIirBCoefficientArray(uint16_t filterNumber);

// Returns the number of B coefficients.
uint32_t filter_getIirBCoefficientCount();

// Returns the size of the yQueue.
uint32_t filter_getYQueueSize();

// Returns the decimation value.
uint16_t filter_getDecimationValue();

// Returns the address of xQueue.
queue_t *filter_getXQueue();

// Returns the address of yQueue.
queue_t *filter_getYQueue();

// Returns the address of zQueue for a specific filter number.
queue_t *filter_getZQueue(uint16_t filterNumber);

// Returns the address of the IIR output-queue for a specific filter-number.
queue_t *filter_getIirOutputQueue(uint16_t filterNumber);

const static double firCoefficients[FIR_FILTER_B_COEFFICIENT_COUNT] = {
6.0546138291524580e-04, 
5.2507143315816808e-04, 
3.8449091273497492e-04, 
1.7398667198943567e-04, 
-1.1360489933812547e-04, 
-4.7488111477505081e-04, 
-8.8813878355243757e-04, 
-1.3082618178330387e-03, 
-1.6663618496958314e-03, 
-1.8755700366395165e-03, 
-1.8432363328956792e-03, 
-1.4884258721946939e-03, 
-7.6225514927495924e-04, 
3.3245249129102442e-04, 
1.7262548802264024e-03, 
3.2768418720461037e-03, 
4.7744814146402663e-03, 
5.9606317814625432e-03, 
6.5591485566693659e-03, 
6.3172870282898136e-03, 
5.0516421325067186e-03, 
2.6926388910163230e-03, 
-6.7950808876295532e-04, 
-4.8141100026235107e-03,
-1.6891587875314695e-02, 
-1.8646984919460430e-02, 
-1.8149697899171331e-02, 
-1.4875876924659621e-02, 
-8.5110608558055904e-03, 
9.8848931917531373e-04, 
1.3360421141854539e-02, 
2.8033301290965273e-02, 
4.4158668590262247e-02, 
6.0676486642845945e-02, 
7.6408062643720479e-02, 
9.0166807113026937e-02, 
1.0087463525517464e-01, 
1.0767073207835436e-01, 
1.1000000000011002e-01, 
1.0767073207835436e-01, 
1.0087463525517464e-01, 
9.0166807113026937e-02, 
7.6408062643720479e-02, 
6.0676486642845945e-02, 
4.4158668590262247e-02, 
2.8033301290965273e-02, 
1.3360421141854539e-02, 
9.8848931917531373e-04, 
-8.5110608558055904e-03, 
-1.4875876924659621e-02, 
-1.8149697899171331e-02, 
-1.8646984919460430e-02, 
-1.6891587875314695e-02, 
-1.3538595939050732e-02, 
-9.2899200682683512e-03, 
-4.8141100026235107e-03, 
-6.7950808876295532e-04, 
2.6926388910163230e-03, 
5.0516421325067186e-03, 
6.3172870282898136e-03, 
6.5591485566693659e-03, 
5.9606317814625432e-03, 
4.7744814146402663e-03, 
3.2768418720461037e-03, 
1.7262548802264024e-03, 
3.3245249129102442e-04, 
-7.6225514927495924e-04, 
-1.4884258721946939e-03, 
-1.8432363328956792e-03, 
-1.8755700366395165e-03, 
-1.6663618496958314e-03, 
-1.3082618178330387e-03, 
-8.8813878355243757e-04, 
-4.7488111477505081e-04, 
-1.1360489933812547e-04, 
1.7398667198943567e-04, 
3.8449091273497492e-04, 
5.2507143315816808e-04, 
6.0546138291524580e-04};

const static double iirACoefficientConstants[FILTER_FREQUENCY_COUNT][IIR_A_COEFFICIENT_COUNT] = {
{-5.9637727070164059e+00, 1.9125339333078287e+01, -4.0341474540744301e+01, 6.1537466875369077e+01, -7.0019717951472558e+01, 6.0298814235239249e+01, -3.8733792862566574e+01, 1.7993533279581207e+01, -5.4979061224868158e+00, 9.0332828533800469e-01},
{-4.6377947119071408e+00, 1.3502215749461552e+01, -2.6155952405269698e+01, 3.8589668330738235e+01, -4.3038990303252490e+01, 3.7812927599536991e+01, -2.5113598088113683e+01, 1.2703182701888030e+01, -4.2755083391143280e+00, 9.0332828533799747e-01},
{-3.0591317915750937e+00, 8.6417489609637492e+00, -1.4278790253808838e+01, 2.1302268283304294e+01, -2.2193853972079211e+01, 2.0873499791105424e+01, -1.3709764520609379e+01, 8.1303553577931567e+00, -2.8201643879900473e+00, 9.0332828533799880e-01},
{-1.4071749185996751e+00, 5.6904141470697542e+00, -5.7374718273676306e+00, 1.1958028362868905e+01, -8.5435280598354630e+00, 1.1717345583835968e+01, -5.5088290876998647e+00, 5.3536787286077674e+00, -1.2972519209655595e+00, 9.0332828533800047e-01},
{8.2010906117760318e-01, 5.1673756579268604e+00, 3.2580350909220925e+00, 1.0392903763919193e+01, 4.8101776408669084e+00, 1.0183724507092508e+01, 3.1282000712126754e+00, 4.8615933365571991e+00, 7.5604535083144919e-01, 9.0332828533800047e-01},
{2.7080869856154530e+00, 7.8319071217995795e+00, 1.2201607990980769e+01, 1.8651500443681677e+01, 1.8758157568004620e+01, 1.8276088095999114e+01, 1.1715361303018966e+01, 7.3684394621254015e+00, 2.4965418284512091e+00, 9.0332828533801224e-01},
{4.9479835250075892e+00, 1.4691607003177602e+01, 2.9082414772101060e+01, 4.3179839108869331e+01, 4.8440791644688879e+01, 4.2310703962394342e+01, 2.7923434247706432e+01, 1.3822186510471010e+01, 4.5614664160654357e+00, 9.0332828533799958e-01},
{6.1701893352279864e+00, 2.0127225876810336e+01, 4.2974193398071691e+01, 6.5958045321253465e+01, 7.5230437667866624e+01, 6.4630411355739881e+01, 4.1261591079244141e+01, 1.8936128791950541e+01, 5.6881982915180327e+00, 9.0332828533799836e-01},
{7.4092912870072398e+00, 2.6857944460290135e+01, 6.1578787811202247e+01, 9.8258255839887340e+01, 1.1359460153696304e+02, 9.6280452143026153e+01, 5.9124742025776442e+01, 2.5268527576524235e+01, 6.8305064480743178e+00, 9.0332828533800158e-01},
{8.5743055776347692e+00, 3.4306584753117903e+01, 8.4035290411037124e+01, 1.3928510844056831e+02, 1.6305115418161643e+02, 1.3648147221895812e+02, 8.0686288623299902e+01, 3.2276361903872186e+01, 7.9045143816244918e+00, 9.0332828533799903e-01}
};

const static double iirBCoefficientConstants[FILTER_FREQUENCY_COUNT][IIR_B_COEFFICIENT_COUNT] = {
{9.0928661148176830e-10, 0.0000000000000000e+00, -4.5464330574088414e-09, 0.0000000000000000e+00, 9.0928661148176828e-09, 0.0000000000000000e+00, -9.0928661148176828e-09, 0.0000000000000000e+00, 4.5464330574088414e-09, 0.0000000000000000e+00, -9.0928661148176830e-10},
{9.0928661148203093e-10, 0.0000000000000000e+00, -4.5464330574101550e-09, 0.0000000000000000e+00, 9.0928661148203099e-09, 0.0000000000000000e+00, -9.0928661148203099e-09, 0.0000000000000000e+00, 4.5464330574101550e-09, 0.0000000000000000e+00, -9.0928661148203093e-10},
{9.0928661148196858e-10, 0.0000000000000000e+00, -4.5464330574098431e-09, 0.0000000000000000e+00, 9.0928661148196862e-09, 0.0000000000000000e+00, -9.0928661148196862e-09, 0.0000000000000000e+00, 4.5464330574098431e-09, 0.0000000000000000e+00, -9.0928661148196858e-10},
{9.0928661148203424e-10, 0.0000000000000000e+00, -4.5464330574101715e-09, 0.0000000000000000e+00, 9.0928661148203430e-09, 0.0000000000000000e+00, -9.0928661148203430e-09, 0.0000000000000000e+00, 4.5464330574101715e-09, 0.0000000000000000e+00, -9.0928661148203424e-10},
{9.0928661148203041e-10, 0.0000000000000000e+00, -4.5464330574101516e-09, 0.0000000000000000e+00, 9.0928661148203033e-09, 0.0000000000000000e+00, -9.0928661148203033e-09, 0.0000000000000000e+00, 4.5464330574101516e-09, 0.0000000000000000e+00, -9.0928661148203041e-10},
{9.0928661148164309e-10, 0.0000000000000000e+00, -4.5464330574082152e-09, 0.0000000000000000e+00, 9.0928661148164304e-09, 0.0000000000000000e+00, -9.0928661148164304e-09, 0.0000000000000000e+00, 4.5464330574082152e-09, 0.0000000000000000e+00, -9.0928661148164309e-10},
{9.0928661148193684e-10, 0.0000000000000000e+00, -4.5464330574096843e-09, 0.0000000000000000e+00, 9.0928661148193686e-09, 0.0000000000000000e+00, -9.0928661148193686e-09, 0.0000000000000000e+00, 4.5464330574096843e-09, 0.0000000000000000e+00, -9.0928661148193684e-10},
{9.0928661148192133e-10, 0.0000000000000000e+00, -4.5464330574096065e-09, 0.0000000000000000e+00, 9.0928661148192131e-09, 0.0000000000000000e+00, -9.0928661148192131e-09, 0.0000000000000000e+00, 4.5464330574096065e-09, 0.0000000000000000e+00, -9.0928661148192133e-10},
{9.0928661148181700e-10, 0.0000000000000000e+00, -4.5464330574090846e-09, 0.0000000000000000e+00, 9.0928661148181692e-09, 0.0000000000000000e+00, -9.0928661148181692e-09, 0.0000000000000000e+00, 4.5464330574090846e-09, 0.0000000000000000e+00, -9.0928661148181700e-10},
{9.0928661148189248e-10, 0.0000000000000000e+00, -4.5464330574094626e-09, 0.0000000000000000e+00, 9.0928661148189252e-09, 0.0000000000000000e+00, -9.0928661148189252e-09, 0.0000000000000000e+00, 4.5464330574094626e-09, 0.0000000000000000e+00, -9.0928661148189248e-10}
};

#endif /* FILTER_H_ */