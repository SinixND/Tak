#ifndef IG20260117152251
#define IG20260117152251

#include "Game.h"
#include "unity.h"

void testInitGame( void )
{
    //* EXECUTE
    Game game0 = initGame( 0 );

    //* VERIFY
    TEST_ASSERT_EQUAL_INT(
        5,
        game0.gameSettings.boardWidth
    );

    //* CLEANUP
    deinitGame( &game0 );

    //* EXECUTE
    Game game3 = initGame( 3 );

    //* VERIFY
    TEST_ASSERT_EQUAL_INT(
        3,
        game3.gameSettings.boardWidth
    );

    //* CLEANUP
    deinitGame( &game3 );
}

#endif
