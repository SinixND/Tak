#include "StackBufferSystem.h"
#include "StackBuffer.h"
#include "StackSystem.h"
#include "StoneType.h"
#include <assert.h>

StackBuffer newStackBuffer( void )
{
    StackBuffer buffer = {
        newStack(),
        STONE_TYPE_NONE
    };

    return buffer;
}

StackBuffer appendToBottom(
    StackBuffer buffer,
    PlayerId const playerId
)
{
    assert(
        ( playerId == PLAYER_WHITE || playerId == PLAYER_BLACK )
        && "Invalid playerId"
    );

    //* Add affiliation
    buffer.stack.affiliations[buffer.stack.count] = playerId;

    //* Increase stack count
    ++buffer.stack.count;

    return buffer;
}

StackBuffer dropFromBottom( StackBuffer buffer )
{
    //* Increase stack count
    --buffer.stack.count;

    //* Add affiliation
    buffer.stack.affiliations[buffer.stack.count] = PLAYER_NONE;

    return buffer;
}
