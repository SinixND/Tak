#include "Game.h"

#include "GameSystem.h"
#include "PlacementSystem.h"
#include "PlayerId.h"
#include "StoneType.h"
#include "unity.h"

void testPlaceStoneOnBoard( void )
{
    //* SETUP
    Game game = newGame( 0 );

    //*EXECUTE
    game = placeStoneOnBoard(
        game,
        PLAYER_WHITE,
        0,
        0,
        STONE_TYPE_FLAT
    );

    //* VERIFY
    TEST_ASSERT_EQUAL_INT(
        20,
        game.players.regularReserves[1]
    );

    TEST_ASSERT_EQUAL_INT(
        1,
        game.board.stacks[0].height
    );

    TEST_ASSERT_EQUAL_INT(
        PLAYER_WHITE,
        game.board.stacks[0].affiliations[0]
    );

    TEST_ASSERT_EQUAL_INT(
        (int)STONE_TYPE_FLAT,
        game.board.types[0]
    );

    //*EXECUTE
    game = placeStoneOnBoard(
        game,
        PLAYER_BLACK,
        0,
        0,
        STONE_TYPE_WALL
    );

    //* VERIFY
    TEST_ASSERT_EQUAL_INT(
        20,
        game.players.regularReserves[1]
    );

    TEST_ASSERT_EQUAL_INT(
        2,
        game.board.stacks[0].height
    );

    TEST_ASSERT_EQUAL_INT(
        PLAYER_BLACK,
        game.board.stacks[0].affiliations[1]
    );

    TEST_ASSERT_EQUAL_INT(
        (int)STONE_TYPE_WALL,
        game.board.types[0]
    );

    //*EXECUTE
    game = placeStoneOnBoard(
        game,
        PLAYER_WHITE,
        0,
        0,
        STONE_TYPE_CAP
    );

    //* VERIFY
    TEST_ASSERT_EQUAL_INT(
        0,
        game.players.capstoneReserves[1]
    );

    TEST_ASSERT_EQUAL_INT(
        3,
        game.board.stacks[0].height
    );

    TEST_ASSERT_EQUAL_INT(
        PLAYER_WHITE,
        game.board.stacks[0].affiliations[2]
    );

    TEST_ASSERT_EQUAL_INT(
        (int)STONE_TYPE_CAP,
        game.board.types[0]
    );
}
