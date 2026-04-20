#include "Demo.h"

#include "App.h"
#include "Game.h"
#include "StoneTypeId.h"
#include <stdbool.h>

void demo( App* const pApp )
{
    placeStone(
        &pApp->game,
        PLAYER_WHITE,
        0,
        STONE_TYPE_FLAT
    );

    liftStack(
        &pApp->game,
        0
    );

    dropStone(
        &pApp->game,
        0
    );

    liftStone(
        &pApp->game,
        0,
        false
    );

    dropStack(
        &pApp->game,
        0
    );

    takeStone(
        &pApp->game,
        0
    );

    placeStone(
        &pApp->game,
        PLAYER_BLACK,
        1,
        STONE_TYPE_STANDING
    );

    placeStone(
        &pApp->game,
        PLAYER_WHITE,
        2,
        STONE_TYPE_FLAT
    );

    liftStack(
        &pApp->game,
        1
    );

    dropStack(
        &pApp->game,
        2
    );

    placeStone(
        &pApp->game,
        PLAYER_BLACK,
        3,
        STONE_TYPE_STANDING
    );

    placeStone(
        &pApp->game,
        PLAYER_WHITE,
        4,
        STONE_TYPE_FLAT
    );

    liftStack(
        &pApp->game,
        3
    );

    dropStack(
        &pApp->game,
        4
    );

    liftStack(
        &pApp->game,
        4
    );
}
