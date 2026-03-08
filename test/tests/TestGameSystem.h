#ifndef IG20260117152251
#define IG20260117152251

#include "BoardSystem.h"
#include "Game.h"
#include "GameSystem.h"
#include "PlayerId.h"
#include "StoneType.h"
#include "unity.h"

void testNewGame( void )
{
    Game game0 = newGame( 0 );

    TEST_ASSERT_EQUAL_INT( 5, game0.board.width );

    Game game3 = newGame( 3 );

    TEST_ASSERT_EQUAL_INT( 3, game3.board.width );

    Game game8 = newGame( 8 );

    TEST_ASSERT_EQUAL_INT( 8, game8.board.width );
}

void testPlaceStone( void )
{
    Game game = newGame( 0 );

    placeStone(
        &game,
        PLAYER_WHITE,
        0,
        0,
        STONE_TYPE_FLAT
    );

    TEST_ASSERT_EQUAL_INT( 20, game.players.regularReserves[PLAYER_WHITE] );
    TEST_ASSERT_EQUAL_INT( 1, game.board.counts[0] );
    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, game.board.stoneIds[0] );
    TEST_ASSERT_EQUAL_INT( PLAYER_NONE, game.board.stoneIds[1] );
    TEST_ASSERT_EQUAL_INT( STONE_TYPE_FLAT, game.board.types[0] );

    placeStone(
        &game,
        PLAYER_BLACK,
        1,
        0,
        STONE_TYPE_STANDING
    );

    TEST_ASSERT_EQUAL_INT( 20, game.players.regularReserves[PLAYER_BLACK] );
    TEST_ASSERT_EQUAL_INT( 1, game.board.counts[1] );
    TEST_ASSERT_EQUAL_INT( PLAYER_BLACK, game.board.stoneIds[1 * 43] );
    TEST_ASSERT_EQUAL_INT( PLAYER_NONE, game.board.stoneIds[1] );
    TEST_ASSERT_EQUAL_INT( STONE_TYPE_STANDING, game.board.types[1] );

    placeStone(
        &game,
        PLAYER_WHITE,
        3,
        0,
        STONE_TYPE_CAP
    );

    TEST_ASSERT_EQUAL_INT( 0, game.players.capstoneReserves[PLAYER_WHITE] );
    TEST_ASSERT_EQUAL_INT( 1, game.board.counts[3] );
    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, game.board.stoneIds[3 * 43] );
    TEST_ASSERT_EQUAL_INT( PLAYER_NONE, game.board.stoneIds[3 * 43 + 1] );
    TEST_ASSERT_EQUAL_INT( STONE_TYPE_CAP, game.board.types[3] );
}

void testPickUpStack( void )
{
    Game game = newGame( 3 );

    placeStone(
        &game,
        PLAYER_WHITE,
        0,
        0,
        STONE_TYPE_FLAT
    );

    placeOntoStack(
        &game.board,
        0,
        PLAYER_BLACK,
        STONE_TYPE_FLAT
    );

    placeOntoStack(
        &game.board,
        0,
        PLAYER_WHITE,
        STONE_TYPE_STANDING
    );

    placeOntoStack(
        &game.board,
        0,
        PLAYER_BLACK,
        STONE_TYPE_CAP
    );

    pickUpStack(
        &game,
        0,
        0
    );

    TEST_ASSERT_EQUAL_INT( STONE_TYPE_CAP, game.stackBuffer.type );
    TEST_ASSERT_EQUAL_INT( 3, game.stackBuffer.count );
    TEST_ASSERT_EQUAL_INT( PLAYER_BLACK, game.stackBuffer.stoneIds[0] );
    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, game.stackBuffer.stoneIds[1] );
    TEST_ASSERT_EQUAL_INT( PLAYER_BLACK, game.stackBuffer.stoneIds[2] );
    TEST_ASSERT_EQUAL_INT( PLAYER_NONE, game.stackBuffer.stoneIds[3] );
    TEST_ASSERT_EQUAL_INT( PLAYER_NONE, game.stackBuffer.stoneIds[BOARD_WIDTH_MAX - 1] );

    TEST_ASSERT_EQUAL_INT( STONE_TYPE_FLAT, game.board.types[0] );
    TEST_ASSERT_EQUAL_INT( 1, game.board.counts[0] );
    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, game.board.stoneIds[0] );
}
#endif
