#ifndef IG20260507160740
#define IG20260507160740

#include "InputBuffer.h"
#include <stdbool.h>
#include <stdint.h>

/// Struct to track simulation steps
typedef struct Simulation
{
    uint16_t inputIdx;
} Simulation;

/// Return initialized object
Simulation newSimulation( void );

/// Get next simulated input
bool simulateInput(
    InputBuffer* const pInputBuffer,
    Simulation* const pSimulation
);

#endif
