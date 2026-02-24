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
    TEST_ASSERT_EQUAL_INT(
        5,
        game0.matchConfigs.boardWidth
    );

    TEST_ASSERT_EQUAL_INT(
        0,
        game0.players.stonesInPlay[1]
    );

    TEST_ASSERT_EQUAL_INT(
        21,
        game0.players.regularReserves[1]
    );

    TEST_ASSERT_EQUAL_INT(
        1,
        game0.players.capstoneReserves[1]
    );

    TEST_ASSERT_EQUAL_INT(
        (int)NO_STONE,
        game0.board.types[1]
    );

    TEST_ASSERT_EQUAL_INT(
        0,
        game0.board.stacks[1].height
    );

    TEST_ASSERT_EQUAL_INT(
        0,
        game0.board.stacks[1].affiliations[0]
    );

    //* EXECUTE
    Game game3 = newGame( 3 );

    //* VERIFY
    TEST_ASSERT_EQUAL_INT(
        3,
        game3.matchConfigs.boardWidth
    );

    TEST_ASSERT_EQUAL_INT(
        0,
        game3.players.stonesInPlay[1]
    );

    TEST_ASSERT_EQUAL_INT(
        10,
        game3.players.regularReserves[1]
    );

    TEST_ASSERT_EQUAL_INT(
        0,
        game3.players.capstoneReserves[1]
    );

    TEST_ASSERT_EQUAL_INT(
        (int)NO_STONE,
        game3.board.types[1]
    );

    TEST_ASSERT_EQUAL_INT(
        0,
        game3.board.stacks[1].height
    );

    TEST_ASSERT_EQUAL_INT(
        0,
        game3.board.stacks[1].affiliations[0]
    );
}

#endif
