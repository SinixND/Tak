#include "StackSystem.h"

#include "GameConstants.h"
#include "PlayerId.h"
#include <assert.h>

Stack newStack( void )
{
    Stack stack = { 0 };

    for ( int idx = 0; idx < STONES_MAX; ++idx )
    {
        stack.affiliations[idx] = PLAYER_NONE;
    }

    return stack;
}

