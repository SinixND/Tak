#include "InputBuffer.h"

#include "InputId.h"
#include "Keymap.h"
#include "PlayerId.h"
#include <assert.h>

InputBuffer newInputBuffer( void )
{
    return (InputBuffer){
        // TODO: NONE?
        .playerId = PLAYER_WHITE,
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

    return pInputBuffer->keymap.commands[contextId][pInputBuffer->lastInput];
}
