#ifndef IG20260117152251
#define IG20260117152251

#include "Game.h"
#include "GameSystem.h"
#include "unity.h"

void testNewGame( void )
{
    //* EXECUTE
    Game game0 = newGame( BWD_NONE );

    //* VERIFY
    TEST_ASSERT_EQUAL_INT( BWD_5, game0.matchConfigs.boardWidthId );

    //* EXECUTE
    Game game3 = newGame( BWD_3 );

    //* VERIFY
    TEST_ASSERT_EQUAL_INT( BWD_3, game3.matchConfigs.boardWidthId );
}

#endif
