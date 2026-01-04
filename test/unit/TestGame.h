#ifndef IG20260104183517
#define IG20260104183517

#include "Game.h"
#include <unity.h>

void testInitGame( void )
{
    //* SETUP
    int const boardWidth = 3;

    //* EXECUTE
    Game game = initGame( 0 );

    //* VERIFY
    // TEST_ASSERT_EQUAL_INT( 1, game.gameSettings.boardWidth );

    //* CLEANUP
    deinitGame( &game );
}

#endif
