#include "DemoSystem.h"

#include "App.h"
#include "BoardSystem.h"
#include "GameSystem.h"

void demo( App* const app )
{
    placeStone(
        &app->game,
        PLAYER_WHITE,
        0,
        0,
        STONE_TYPE_FLAT
    );

    undo( &app->game );
    redo( &app->game );

    putOntoStack(
        &app->game.board,
        PLAYER_BLACK,
        0,
        STONE_TYPE_STANDING
    );

    liftStack(
        &app->game,
        0,
        0
    );

    dropStone(
        &app->game,
        0,
        1
    );
}
