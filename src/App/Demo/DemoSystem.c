#include "DemoSystem.h"

#include "EventExecution.h"
#include "Game.h"

void demo( App* pApp )
{
    Event* pEvent = &pApp->gameEvent;

    pEvent->actionType = ACTION_TYPE_PLACE;
    pEvent->playerId = PLAYER_WHITE;
    pEvent->stoneType = STONE_TYPE_FLAT;
    pEvent->fileX = FILE_A;
    pEvent->rankY = RANK_1;

    executeEvent( pApp );
    takeStone(
        &pApp->game,
        0
    );
}
