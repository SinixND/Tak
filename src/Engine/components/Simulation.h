#ifndef IG20260507160740
#define IG20260507160740

#include "EngineConstants.h"
#include "InputBuffer.h"
#include "InputId.h"
#include <stdbool.h>

typedef struct Simulation
{
    InputId inputs[MAX_DEMO_SIZE];
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
