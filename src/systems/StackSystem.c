#include "StackSystem.h"

#include "GameConstants.h"
#include "PlayerId.h"
#include <assert.h>

Stack newStack( void )
{
    Stack stack = { .height = 0 };

    for ( int idx = 0; idx < STONES_MAX; ++idx )
    {
        stack.affiliations[idx] = PLAYER_NONE;
    }

    return stack;
}

Stack addStoneToStack(
    Stack stack,
    PlayerId const playerId
)
{
    assert(
        ( playerId == PLAYER_WHITE || playerId == PLAYER_BLACK )
        && "Invalid playerId"
    );

    //* Add affiliation
    stack.affiliations[stack.height] = playerId;

    //* Increase stack height
    ++stack.height;

    return stack;
}
