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

void testPlaceStone( void )
{
    //* SETUP
    Game game = newGame( 0 );

    //*EXECUTE
    game = placeStone(
        game,
        PLAYER_WHITE,
        0,
        0,
        STONE_TYPE_FLAT
    );

    //* VERIFY
    TEST_ASSERT_EQUAL_INT( 20, game.players.regularReserves[PLAYER_WHITE] );
    TEST_ASSERT_EQUAL_INT( 1, game.board.stacks[0].count );
    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, game.board.stacks[0].stoneIds[0] );
    TEST_ASSERT_EQUAL_INT( PLAYER_NONE, game.board.stacks[0].stoneIds[1] );
    TEST_ASSERT_EQUAL_INT( STONE_TYPE_FLAT, game.board.types[0] );

    //*EXECUTE
    game = placeStone(
        game,
        PLAYER_BLACK,
        1,
        0,
        STONE_TYPE_STANDING
    );

    //* VERIFY
    TEST_ASSERT_EQUAL_INT( 20, game.players.regularReserves[PLAYER_BLACK] );
    TEST_ASSERT_EQUAL_INT( 1, game.board.stacks[1].count );
    TEST_ASSERT_EQUAL_INT( PLAYER_BLACK, game.board.stacks[1].stoneIds[0] );
    TEST_ASSERT_EQUAL_INT( PLAYER_NONE, game.board.stacks[0].stoneIds[1] );
    TEST_ASSERT_EQUAL_INT( STONE_TYPE_STANDING, game.board.types[1] );

    //*EXECUTE
    game = placeStone(
        game,
        PLAYER_WHITE,
        3,
        0,
        STONE_TYPE_CAP
    );

    //* VERIFY
    TEST_ASSERT_EQUAL_INT( 0, game.players.capstoneReserves[PLAYER_WHITE] );
    TEST_ASSERT_EQUAL_INT( 1, game.board.stacks[3].count );
    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, game.board.stacks[3].stoneIds[0] );
    TEST_ASSERT_EQUAL_INT( PLAYER_NONE, game.board.stacks[3].stoneIds[1] );
    TEST_ASSERT_EQUAL_INT( STONE_TYPE_CAP, game.board.types[3] );
}

#endif
