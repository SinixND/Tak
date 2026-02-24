#include "Game.h"

#include "GameSystem.h"
#include "PlacementSystem.h"
#include "StoneType.h"
#include "unity.h"

void testPlaceStoneOnBoard( void )
{
    //* SETUP
    Game game = newGame( 0 );

    //*EXECUTE
    game = placeStoneOnBoard(
        game,
        1,
        0,
        0,
        FLAT
    );

    //* VERIFY
    TEST_ASSERT_EQUAL_INT(
        20,
        game.players.regularReserves[1]
    );

    TEST_ASSERT_EQUAL_INT(
        1,
        game.board.heights[0]
    );

    TEST_ASSERT_EQUAL_INT(
        1,
        game.board.stacks[0][0]
    );

    TEST_ASSERT_EQUAL_INT(
        (int)FLAT,
        game.board.types[0]
    );

    //*EXECUTE
    game = placeStoneOnBoard(
        game,
        2,
        0,
        0,
        WALL
    );

    //* VERIFY
    TEST_ASSERT_EQUAL_INT(
        20,
        game.players.regularReserves[1]
    );

    TEST_ASSERT_EQUAL_INT(
        2,
        game.board.heights[0]
    );

    TEST_ASSERT_EQUAL_INT(
        2,
        game.board.stacks[0][1]
    );

    TEST_ASSERT_EQUAL_INT(
        (int)WALL,
        game.board.types[0]
    );

    //*EXECUTE
    game = placeStoneOnBoard(
        game,
        1,
        0,
        0,
        CAP
    );

    //* VERIFY
    TEST_ASSERT_EQUAL_INT(
        0,
        game.players.capstoneReserves[1]
    );

    TEST_ASSERT_EQUAL_INT(
        3,
        game.board.heights[0]
    );

    TEST_ASSERT_EQUAL_INT(
        1,
        game.board.stacks[0][2]
    );

    TEST_ASSERT_EQUAL_INT(
        (int)CAP,
        game.board.types[0]
    );
}
