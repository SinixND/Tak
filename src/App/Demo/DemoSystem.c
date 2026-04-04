#include "DemoSystem.h"

#include "App.h"
#include "AppSystem.h"
#include "BoardSystem.h"
#include "GameEvent.h"
#include "GameEventSystem.h"
#include "GameSystem.h"

void demo( App* const pApp )
{
    placeStone(
        &pApp->game,
        PLAYER_WHITE,
        0,
        0,
        STONE_TYPE_FLAT
    );

    undo( pApp );
    redo( pApp );

    putOntoStack(
        &pApp->game.board,
        PLAYER_BLACK,
        0,
        STONE_TYPE_STANDING
    );

    liftStack(
        &pApp->game,
        0,
        0
    );

    dropStone(
        &pApp->game,
        0,
        1
    );

    GameEvent event = newGameEvent();

    validateEvent(
        &event,
        &pApp->game
    );
}
