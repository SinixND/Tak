#ifndef IG20260507160740
#define IG20260507160740

#include "InputBuffer.h"
#include <stdbool.h>

typedef struct Simulation
{
    int inputIdx;
} Simulation;

/// Return initialized Simulation object
Simulation newSimulation( void );

/// Get next simulated input
bool simulateInput(
    InputBuffer* const pInputBuffer,
    Simulation* const pSimulation
);

#endif
