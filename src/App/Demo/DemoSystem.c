#include "DemoSystem.h"

#include "Redo.h"
#include "TurnLogic.h"
#include "Undo.h"

void demo( App* pApp )
{
    GameEvent* pGameEvent = &pApp->gameEvent;

    pGameEvent->actionType = ACTION_TYPE_PLACE;
    pGameEvent->playerId = PLAYER_WHITE;
    pGameEvent->stoneType = STONE_TYPE_FLAT;
    pGameEvent->fileX = FILE_A;
    pGameEvent->rankY = RANK_1;

    executeTurn( pApp );

    undo( pApp );
    redo( pApp );
}
