#include "DemoSystem.h"

#include "Redo.h"
#include "TurnLogic.h"
#include "Undo.h"

void demo( App* pApp )
{
    pApp->gameEvent.actionType = ACTION_TYPE_PLACE;
    pApp->gameEvent.playerId = PLAYER_WHITE;
    pApp->gameEvent.stoneType = STONE_TYPE_FLAT;
    pApp->gameEvent.fileX = FILE_A;
    pApp->gameEvent.rankY = RANK_1;

    executeTurn( pApp );

    undo( pApp );
    redo( pApp );
}
