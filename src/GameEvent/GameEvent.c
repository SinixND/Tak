#include "GameEvent.h"

#include "ActionTypeId.h"
#include "GameEvent.h"
#include "StoneTypeId.h"
#include <assert.h>
#include <stdbool.h>

GameEvent newGameEvent( void )
{
    return (GameEvent){
        .playerId = PLAYER_NONE,
        .actionType = ACTION_TYPE_NONE,
        .stoneType = STONE_TYPE_NONE,
        .fileX = FILE_NONE,
        .rankY = RANK_NONE,
        .dropCount = 0,
    };
}

