#include "StackSystem.h"

#include "GameConstants.h"
#include "PlayerId.h"
#include <assert.h>

Stack newStack( void )
{
    Stack stack = { .count = 0 };

    for ( int idx = 0; idx < STONES_MAX; ++idx )
    {
        stack.affiliations[idx] = PLAYER_NONE;
    }

    return stack;
}

Stack putOnTop(
    Stack stack,
    PlayerId const playerId
)
{
    assert(
        ( playerId == PLAYER_WHITE || playerId == PLAYER_BLACK )
        && "Invalid playerId"
    );

    //* Add affiliation
    stack.affiliations[stack.count] = playerId;

    //* Increase stack count
    ++stack.count;

    return stack;
}

Stack takeFromTop( Stack stack )
{
    assert(
        stack.count > 0
        && "Can only undo from stack with count > 0"
    );

    //* Decrease stack count
    --stack.count;

    //* Remove affiliation
    stack.affiliations[stack.count] = PLAYER_NONE;

    return stack;
}
