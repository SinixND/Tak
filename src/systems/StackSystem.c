#include "StackSystem.h"

#include "GameConstants.h"
#include "PlayerId.h"
#include <assert.h>

Stack newStack( void )
{
    Stack stack = { .count = 0 };

    for ( int idx = 0; idx < STONES_MAX; ++idx )
    {
        stack.stoneIds[idx] = PLAYER_NONE;
    }

    return stack;
}

Stack pushOntoStack(
    Stack stack,
    PlayerId const playerId
)
{
    assert(
        ( playerId == PLAYER_WHITE || playerId == PLAYER_BLACK )
        && "Invalid playerId"
    );

    //* Add playerId
    stack.stoneIds[stack.count] = playerId;

    //* Increase stack count
    ++stack.count;

    return stack;
}
