#include "Demo.h"

#include "App.h"
#include "Board.h"
#include "Game.h"
#include "PlayerId.h"
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

    //* Prepare
    placeStone(
        &pApp->game,
        PLAYER_BLACK,
        1,
        STONE_TYPE_FLAT
    );

    putOntoStack(
        &pApp->game.board,
        PLAYER_WHITE,
        1,
        STONE_TYPE_FLAT
    );

    putOntoStack(
        &pApp->game.board,
        PLAYER_BLACK,
        1,
        STONE_TYPE_FLAT
    );

    putOntoStack(
        &pApp->game.board,
        PLAYER_WHITE,
        1,
        STONE_TYPE_STANDING
    );

    liftStack(
        &pApp->game,
        1
    );
}
