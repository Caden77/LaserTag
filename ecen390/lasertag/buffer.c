

#include "buffer.h"
#include "stdbool.h"
#include "stdlib.h"

// This implements a dedicated circular buffer for storing values
// from the ADC until they are read and processed by the detector.
// The function of the buffer is similar to a queue or FIFO.

// Uncomment for debug prints
// #define DEBUG
 
#if defined(DEBUG)
#include <stdio.h>
#include "xil_printf.h" // outbyte
#define DPRINTF(...) printf(__VA_ARGS__)
#else
#define DPRINTF(...)
#endif
 
#define BUFFER_SIZE 32768
 
typedef struct {
    uint32_t indexIn; // Points to the next open slot.
    uint32_t indexOut; // Points to the next element to be removed.
    uint32_t elementCount; // Number of elements in the buffer.
    buffer_data_t data[BUFFER_SIZE]; // Values are stored here.
} buffer_t;

volatile static buffer_t buff;

// Initialize the buffer to empty.
void buffer_init(void) {
    // Points to a dynamically-allocated array.
    buff.indexIn = 0;
    buff.indexOut = 0;
    buff.elementCount = 0;
}

// Returns true if the buffer is full
static bool buffer_full() { 
    return buffer_size() == buff.elementCount;
}

// Returns true if the buffer is empty
static bool buffer_empty() {
    return buff.elementCount == 0;
}

// Helper func for buffer_pushover
static void buffer_push(buffer_data_t value) {
    //if we have a buffer
    if (buffer_full()) {
        DPRINTF("writing to a full buffer\n");
    } else {
        //add to the queue
        buff.data[buff.indexIn] = value;
        (buff.elementCount)++;

        //increment the index pointer
        (buff.indexIn)++;
        //go back to beginning if incrementing off last index
        buff.indexIn = buff.indexIn % buffer_size();
    }
}

// Remove a value from the buffer. Return zero if empty.
buffer_data_t buffer_pop(void) {

    if (buffer_empty()) { // If the buffer is empty, return 0
        DPRINTF("popping on empty buffer\n");
        return 0;
    } else {
        //get data
        buffer_data_t dataReturned = buff.data[buff.indexOut];
        (buff.elementCount)--;
        //increment our begin index (aka remove)
        (buff.indexOut)++;
        // go back to the beginning if incrementing off last index
        buff.indexOut = buff.indexOut % buffer_size();
            
        //return data
        return dataReturned;
    }
}


// Add a value to the buffer. Overwrite the oldest value if full.
void buffer_pushover(buffer_data_t value) {
    if (buffer_full()) {
        //if buffer is full

        //overwrite oldest value
        buffer_pop();
        buffer_push(value);
    } else {
        //else add value to the buffer
        buffer_push(value);
    }
}

// Return the number of elements in the buffer.
uint32_t buffer_elements(void) {
    return buff.elementCount;
}

// Return the capacity of the buffer in elements.
uint32_t buffer_size(void) {
    return BUFFER_SIZE;
}
