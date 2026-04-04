#include "InputBufferSystem.h"

#include "InputBuffer.h"
#include "InputId.h"

InputBuffer newInputBuffer( void )
{
    return (InputBuffer){
        .keyboard = INPUT_NONE,
    };
}

