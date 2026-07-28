#include "InputBuffer.h"

#include "InputId.h"
#include "Keymap.h"
#include <assert.h>

InputBuffer newInputBuffer( void )
{
    return (InputBuffer){
        .keymap = newKeymap(),
        .lastInput = INPUT_NONE,
    };
}

CommandId getCommandId(
    InputBuffer const* const pInputBuffer,
    ContextId const contextId
)
{
    assert(
        pInputBuffer
        && "Pointer is nullptr"
    );

    if ( pInputBuffer->lastInput == INPUT_MOUSE )
    {
        assert( pInputBuffer->position[0] );
    }

    return pInputBuffer->keymap.commands[contextId][pInputBuffer->lastInput];
}
