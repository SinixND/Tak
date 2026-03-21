#include "GameEventSystem.h"

#include "GameConstants.h"
#include "GameEvent.h"
#include <stdbool.h>

GameEvent newGameEvent( void )
{
    GameEvent event = {
        0
    };

    for ( int idx = 0; idx < BOARD_WIDTH_MAX; ++idx )
    {
        event.dropCounts[idx] = -1;
    }

    return event;
}

