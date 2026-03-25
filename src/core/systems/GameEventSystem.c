#include "GameEventSystem.h"

#include "DirectionId.h"
#include "FileId.h"
#include "GameConstants.h"
#include "GameEvent.h"
#include "PlayerId.h"
#include "StoneType.h"
#include <stdbool.h>

GameEvent newGameEvent( void )
{
    GameEvent event = {
        .stoneId = PLAYER_NONE,
        .actionType = ACTION_TYPE_NONE,
        .stoneType = STONE_TYPE_NONE,
        .fileX = FILE_NONE,
        .rankY = RANK_NONE,
        .direction = DIR_NONE,
        .liftCount = 0,
        .dropCountsSize = 0,
        .droppedCount = 0
    };

    for ( int idx = 0; idx < BOARD_WIDTH_MAX; ++idx )
    {
        event.dropCounts[idx] = -1;
    }

    return event;
}

