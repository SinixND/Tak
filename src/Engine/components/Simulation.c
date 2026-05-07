#include "Simulation.h"

#include "InputBuffer.h"
#include <stdbool.h>

Simulation newSimulation( void )
{
    return (Simulation){
        .inputIdx = 0,
        .inputs = {
            /// 1
            INPUT_B,
            INPUT_1,
            /// 2
            INPUT_C,
            INPUT_1,
        },
    };
}

bool simulateInput(
    InputBuffer* const pInputBuffer,
    Simulation* const pSimulation
)
{
    if ( pSimulation->inputIdx < 4 )
    {
        ++pSimulation->inputIdx;

        pInputBuffer->lastInput = pSimulation->inputs[pSimulation->inputIdx - 1];

        return true;
    }

    return false;
}

