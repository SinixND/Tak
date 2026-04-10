#include "Event.h"

#include <assert.h>
#include <stdbool.h>

Event newEvent( void )
{
    return (Event){
        .playerId = PLAYER_NONE,
        .actionType = ACTION_TYPE_NONE,
        .stoneType = STONE_TYPE_NONE,
        .squareIdx = -1,
        .dropCount = -1,
    };
}

