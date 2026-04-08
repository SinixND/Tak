#include "Command.h"

#include "DirectionId.h"
#include "GameConstants.h"
#include "PlayerId.h"

Command newCommand( void )
{
    Command command = {
        .playerId = PLAYER_NONE,
        .actionType = ACTION_TYPE_NONE,
        .stoneType = STONE_TYPE_NONE,
        .fileX = FILE_NONE,
        .rankY = RANK_NONE,
        .direction = DIR_NONE,
        .drops = -1,
    };

    for ( int i = 0; i < BOARD_WIDTH_MAX; ++i )
    {
        command.dropCounts[i] = -1;
    }

    return command;
}
