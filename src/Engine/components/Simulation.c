#include "Simulation.h"

#include "InputBuffer.h"
#include "SimulationData.h"
#include <stdbool.h>

Simulation newSimulation( void )
{
    return (Simulation){
        .inputIdx = 0,
    };
}

bool simulateInput(
    InputBuffer* const pInputBuffer,
    Simulation* const pSimulation
)
{
    if ( pSimulation->inputIdx < (int)( sizeof( SIMULATION_DATA ) / sizeof( SIMULATION_DATA[0] ) ) )
    {
        ++pSimulation->inputIdx;

        pInputBuffer->lastInput = SIMULATION_DATA[pSimulation->inputIdx - 1];

        return true;
    }

    return false;
}

