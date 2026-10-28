#include "Simulation.h"

#include "Input.h"
#include "SimulationDataMinimal.h"
#include "Timing_Interface.h"
#include <assert.h>
#include <stdbool.h>

Simulation newSimulation( void )
{
    return (Simulation){
        .inputIdx = 0,
    };
}

bool simulateInput(
    Input* const pInput,
    Simulation* const pSimulation
)
{
    assert(
        pInput
        && "Pointer is nullptr"
    );

    assert(
        pSimulation
        && "Pointer is nullptr"
    );

    if ( pSimulation->inputIdx < (int)( sizeof( SIMULATION_DATA ) / sizeof( SIMULATION_DATA[0] ) ) )
    {
        ++pSimulation->inputIdx;

        pInput->lastInput = SIMULATION_DATA[pSimulation->inputIdx - 1];

        wait( 10 );

        return true;
    }

    return false;
}

