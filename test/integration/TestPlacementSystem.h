#include "Game.h"
#include "PlacementSystem.h"
#include "unity.h"

void testPlaceStoneOnBoard( void )
{
    //* SETUP
    Game game = initGame( 3 );

    int const initialRegularReserves = game.matchConfigs.regularStoneReserves;
    int const initialcapstoneReserves = game.matchConfigs.capstoneReserves;

    //*EXECUTE
    placeStoneOnBoard(
        &game.players,
        &game.board,
        &game.stacks,
        &game.stones,
        0,
        0,
        0,
        FLAT
    );

    //* VERIFY
    TEST_ASSERT_EQUAL_INT(
        -1,
        game.players.regularReserves[0] - initialRegularReserves
    );

    TEST_ASSERT_EQUAL_INT(
        1,
        game.stacks.heights[game.board.stackIdxs[0]]
    );

    TEST_ASSERT_EQUAL_INT(
        0,
        game.stacks.topStoneIdxs[game.board.stackIdxs[0]]
    );

    //*EXECUTE
    placeStoneOnBoard(
        &game.players,
        &game.board,
        &game.stacks,
        &game.stones,
        1,
        0,
        0,
        WALL
    );

    //* VERIFY
    TEST_ASSERT_EQUAL_INT(
        -1,
        game.players.regularReserves[1] - initialRegularReserves
    );

    TEST_ASSERT_EQUAL_INT(
        2,
        game.stacks.heights[game.board.stackIdxs[0]]
    );

    TEST_ASSERT_EQUAL_INT(
        1,
        game.stacks.topStoneIdxs[game.board.stackIdxs[0]]
    );

    //*EXECUTE
    placeStoneOnBoard(
        &game.players,
        &game.board,
        &game.stacks,
        &game.stones,
        0,
        0,
        0,
        CAP
    );

    //* VERIFY
    TEST_ASSERT_EQUAL_INT(
        -1,
        game.players.capstoneReserves[0] - initialcapstoneReserves
    );

    TEST_ASSERT_EQUAL_INT(
        3,
        game.stacks.heights[game.board.stackIdxs[0]]
    );

    TEST_ASSERT_EQUAL_INT(
        2,
        game.stacks.topStoneIdxs[game.board.stackIdxs[0]]
    );

    //* CLEANUP
    deinitGame( &game );
}
