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
}
