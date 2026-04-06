#include "DemoSystem.h"

#include "Redo.h"
#include "TurnLogic.h"
#include "Undo.h"

void demo( App* pApp )
{
    Event* pEvent = &pApp->gameEvent;

    pEvent->actionType = ACTION_TYPE_PLACE;
    pEvent->playerId = PLAYER_WHITE;
    pEvent->stoneType = STONE_TYPE_FLAT;
    pEvent->fileX = FILE_A;
    pEvent->rankY = RANK_1;

    executeTurn( pApp );

    undo( pApp );
    redo( pApp );
}
