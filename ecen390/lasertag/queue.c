
#include <stdbool.h>
#include <stdint.h>
#include "queue.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


// Allocates memory for the queue (the data* pointer) and initializes all
// parts of the data structure. Prints out an error message if malloc() fails
// and calls assert(false) to print-out line-number information and die.
// The queue is empty after initialization. To fill the queue with known
// values (e.g. zeros), call queue_overwritePush() up to queue_size() times.
void queue_init(queue_t *q, queue_size_t size, const char *name) {
        // Points to a dynamically-allocated array.
	    q->data = malloc(size * sizeof(queue_data_t));
	    if (q->data == NULL) abort();
        q->indexIn = 0;
        q->indexOut = 0;
        q->elementCount = 0;
        q->size = size;
        q->underflowFlag = false;
        q->overflowFlag = false;
        // Name for debugging purposes.
	    strncpy(q->name, name, QUEUE_MAX_NAME_SIZE);
	    q->name[QUEUE_MAX_NAME_SIZE-1] = '\0';
}

// Get the user-assigned name for the queue.
const char *queue_name(queue_t *q) {
    return q->name;
}

// Returns the capacity of the queue.
queue_size_t queue_size(queue_t *q) {
    if (q != NULL) {
        return q->size;
    } 
    return QUEUE_RETURN_ERROR_VALUE;
}

// Returns true if the queue is full.
bool queue_full(queue_t *q) {
    if (q != NULL) {
        return q->size == q->elementCount;
    }
}
}

// Returns true if the queue is empty.
bool queue_empty(queue_t *q) {
    if (q != NULL) {
        return q->elementCount == 0;
    }
}

// If the queue is not full, pushes a new element into the queue and clears the
// underflowFlag. IF the queue is full, set the overflowFlag, print an error
// message and DO NOT change the queue.
void queue_push(queue_t *q, queue_data_t value) {
    if (q != NULL) {
        if (queue_full(q)){
            q->overflowFlag = true;
            printf("overflow error\n");
        }
        else {
            //add to the queue
            q->data[q->indexIn] = value;
            (q->elementCount)++;

            //increment our index pointer
            (q->indexIn)++;
            if (q->indexIn >= q->size) {
                //invalid index, rotate
                q->indexIn = 0;
            }

            //set flag
            q->underflowFlag = false;
        }
    }
}

// If the queue is not empty, remove and return the oldest element in the queue.
// If the queue is empty, set the underflowFlag, print an error message, and DO
// NOT change the queue.
queue_data_t queue_pop(queue_t *q) {
    if (q != NULL) {
        if (queue_empty(q)){
            q->underflowFlag = true;
            printf("underflow error\n");
            return QUEUE_RETURN_ERROR_VALUE;
        } else {
            //set flag
            q->overflowFlag = false;

            //get data
            queue_data_t dataReturned = q->data[q->indexOut];
            (q->elementCount)--;

            //increment begin index (remove)
            (q->indexOut)++;
            if (q->indexOut >= q->size) {
                //invalid index, rotate
                q->indexOut = 0;
            }

            //return data
            return dataReturned;
        }
    }
}

// If the queue is full, call queue_pop() and then call queue_push().
// If the queue is not full, just call queue_push().
void queue_overwritePush(queue_t *q, queue_data_t value) {
    if (queue_full(q)) {
        queue_pop(q);
        queue_push(q, value);
    } else {
        queue_push(q, value);
    }
}

// Provides random-access read capability to the queue.
// Low-valued indexes access older queue elements while higher-value indexes
// access newer elements (according to the order that they were added). Print a
// meaningful error message if an error condition is detected.
queue_data_t queue_readElementAt(queue_t *q, queue_index_t index) {
    //error checks
    if (index >= q->elementCount || index < 0) {
        printf("Index out of range\n");
    }

    //index determination
    queue_index_t actual_index = (q->indexOut + index) % q->size;
    if (q->data != NULL) {
        return q->data[actual_index];
    }
}

// Returns a count of the elements currently contained in the queue.
queue_size_t queue_elementCount(queue_t *q) {
    return q->elementCount;
}

// Returns true if an underflow has occurred (queue_pop() called on an empty
// queue).
bool queue_underflow(queue_t *q) {
    return q->underflowFlag;
}

// Returns true if an overflow has occurred (queue_push() called on a full
// queue).
bool queue_overflow(queue_t *q) {
    return q->overflowFlag;
}

// Frees the storage that you malloc'd before.
void queue_garbageCollect(queue_t *q) {
    free(q->data);
}