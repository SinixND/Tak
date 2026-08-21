#include "Simulation.h"

#include "BackendInterface.h"
#include "InputBuffer.h"
#include "SimulationDataMinimal.h"
#include <assert.h>
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
    assert(
        pInputBuffer
        && "Pointer is nullptr"
    );

    assert(
        pSimulation
        && "Pointer is nullptr"
    );

    if ( pSimulation->inputIdx < (int)( sizeof( SIMULATION_DATA ) / sizeof( SIMULATION_DATA[0] ) ) )
    {
        ++pSimulation->inputIdx;

        pInputBuffer->lastInput = SIMULATION_DATA[pSimulation->inputIdx - 1];

        wait( 10 );

        return true;
    }

    return false;
}

