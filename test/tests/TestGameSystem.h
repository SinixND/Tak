#ifndef IG20260117152251
#define IG20260117152251

#include "Game.h"
#include "GameSystem.h"
#include "unity.h"

void testNewGame( void )
{
    //* EXECUTE
    Game game0 = newGame( 0 );

    //* VERIFY
    TEST_ASSERT_EQUAL_INT( 5, game0.matchConfigs.boardWidth );

    //* EXECUTE
    Game game3 = newGame( 3 );

    //* VERIFY
    TEST_ASSERT_EQUAL_INT( 3, game3.matchConfigs.boardWidth );
}

#endif
