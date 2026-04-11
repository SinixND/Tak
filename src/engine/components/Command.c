#include "Command.h"

#include "ActionTypeId.h"
#include "DirectionId.h"
#include "FileId.h"
#include "GameConstants.h"
#include "PlayerId.h"
#include "RankId.h"
#include "StoneTypeId.h"
#include <stdbool.h>

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

    for ( int i = 0; i < BOARD_SIZE_MAX; ++i )
    {
        command.dropCounts[i] = -1;
    }

    return command;
}

bool isCommandComplete( Command const* const command )
{
    switch ( command->actionType )
    {
        default:
        case ACTION_TYPE_NONE:
            return false;

        case ACTION_TYPE_PLACE:
        {
            return (
                ( command->playerId != PLAYER_NONE )
                && ( command->fileX != FILE_NONE )
                && ( command->rankY != RANK_NONE )
                && ( command->stoneType != STONE_TYPE_NONE )
            );
        }

        case ACTION_TYPE_LIFT:
        {
            return (
                ( command->fileX != FILE_NONE )
                && ( command->rankY != RANK_NONE )
            );
        }

        case ACTION_TYPE_DROP:
        {
            return (
                ( command->fileX != FILE_NONE )
                && ( command->rankY != RANK_NONE )
                && ( command->direction != DIR_NONE )
                && ( command->dropCounts[command->drops] > 0 )
            );
        }
    }
}
