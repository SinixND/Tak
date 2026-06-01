#include "Demo.h"

#include "App.h"
#include "Game.h"
#include "PlayerId.h"
#include "StoneTypeId.h"
#include <assert.h>
#include <stdbool.h>

void demo( App* const pApp )
{
    assert(
        pApp
        && "Pointer is nullptr"
    );

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
