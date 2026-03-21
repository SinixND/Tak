#include "GameEventSystem.h"

#include "GameConstants.h"
#include "GameEvent.h"
#include "PlayerId.h"
#include <stdbool.h>

GameEvent newGameEvent( void )
{
    GameEvent event = {
        0
    };

    event.stonePlayerId = PLAYER_NONE;

    for ( int idx = 0; idx < BOARD_WIDTH_MAX; ++idx )
    {
        event.dropCounts[idx] = -1;
    }

    return event;
}

