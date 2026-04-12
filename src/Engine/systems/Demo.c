#include "Demo.h"

#include "App.h"
#include "Game.h"
#include "GameConstants.h"
#include <stdbool.h>

void demo( void )
{
    App app = newApp( BOARD_SIZE_DEFAULT );

    placeStone(
        &app.game,
        PLAYER_WHITE,
        0,
        STONE_TYPE_FLAT
    );

    liftStack(
        &app.game,
        0
    );

    dropStone(
        &app.game,
        0
    );

    liftStone(
        &app.game,
        0,
        false
    );

    dropStack(
        &app.game,
        0
    );

    takeStone(
        &app.game,
        0
    );
}
