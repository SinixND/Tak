#include "Event.h"

#include "ActionTypeId.h"
#include "StoneTypeId.h"
#include <assert.h>
#include <stdbool.h>

Event newEvent( void )
{
    return (Event){
        .playerId = PLAYER_NONE,
        .actionType = ACTION_TYPE_NONE,
        .stoneType = STONE_TYPE_NONE,
        .fileX = FILE_NONE,
        .rankY = RANK_NONE,
        .dropCount = -1,
    };
}

