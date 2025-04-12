#ifndef DATA_H
#define DATA_h

#include "queue.h"

// Function to compute the category of person
// Range from 1 to 4, being 1 the highest 
// level of priority
void computeCategory(People* queue);

// Function to copy data from a to b
void dataCpy(People* a, People* b);

// Function to compare a with b data
int dataCmp(People a, People b);

#endif
