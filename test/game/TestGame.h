#ifndef IG20260117152251
#define IG20260117152251

#include "Game.h"
#include "GameConstants.h"
#include "PlayerId.h"
#include "StoneTypeId.h"
#include "unity.h"

void testNewGame( void )
{
    Game game3 = newGame( 3 );

    TEST_ASSERT_EQUAL_INT( 3, game3.board.size );

    Game game5 = newGame( 5 );

    TEST_ASSERT_EQUAL_INT( 5, game5.board.size );

    Game game8 = newGame( 8 );

    TEST_ASSERT_EQUAL_INT( 8, game8.board.size );
}

void testPlaceStone( void )
{
    Game game = newGame( 5 );

    placeStone(
        &game,
        PLAYER_WHITE,
        0,
        STONE_TYPE_FLAT
    );

    TEST_ASSERT_EQUAL_INT( getReservesRegular( 5 ) - 1, game.reserves.regular[PLAYER_WHITE] );
    TEST_ASSERT_EQUAL_INT( 1, game.board.stoneCounts[0] );
    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, game.board.stoneIds[0] );
    TEST_ASSERT_EQUAL_INT( PLAYER_NONE, game.board.stoneIds[1] );
    TEST_ASSERT_EQUAL_INT( STONE_TYPE_FLAT, game.board.stackTypes[0] );

    placeStone(
        &game,
        PLAYER_BLACK,
        1,
        STONE_TYPE_STANDING
    );

    TEST_ASSERT_EQUAL_INT( getReservesRegular( 5 ) - 1, game.reserves.regular[PLAYER_BLACK] );
    TEST_ASSERT_EQUAL_INT( 1, game.board.stoneCounts[1] );
    TEST_ASSERT_EQUAL_INT( PLAYER_BLACK, game.board.stoneIds[1 * getStackCapacity( 5 )] );
    TEST_ASSERT_EQUAL_INT( PLAYER_NONE, game.board.stoneIds[1] );
    TEST_ASSERT_EQUAL_INT( STONE_TYPE_STANDING, game.board.stackTypes[1] );

    placeStone(
        &game,
        PLAYER_WHITE,
        2,
        STONE_TYPE_CAP
    );

    TEST_ASSERT_EQUAL_INT( getReservesCapstone( 5 ) - 1, game.reserves.capstone[PLAYER_WHITE] );
    TEST_ASSERT_EQUAL_INT( 1, game.board.stoneCounts[2] );
    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, game.board.stoneIds[2 * getStackCapacity( 5 )] );
    TEST_ASSERT_EQUAL_INT( PLAYER_NONE, game.board.stoneIds[2 * getStackCapacity( 5 ) + 1] );
    TEST_ASSERT_EQUAL_INT( STONE_TYPE_CAP, game.board.stackTypes[2] );
}
void testTakeStone( void )
{
    Game game = newGame( 5 );

    placeStone(
        &game,
        PLAYER_WHITE,
        0,
        STONE_TYPE_FLAT
    );

    placeStone(
        &game,
        PLAYER_WHITE,
        1,
        STONE_TYPE_STANDING
    );

    placeStone(
        &game,
        PLAYER_WHITE,
        2,
        STONE_TYPE_CAP
    );

    takeStone(
        &game,
        2
    );

    TEST_ASSERT_EQUAL_INT( getReservesCapstone( 5 ), game.reserves.capstone[PLAYER_WHITE] );
    TEST_ASSERT_EQUAL_INT( 0, game.board.stoneCounts[2] );

    takeStone(
        &game,
        1
    );

    TEST_ASSERT_EQUAL_INT( getReservesRegular( 5 ) - 1, game.reserves.regular[PLAYER_WHITE] );
    TEST_ASSERT_EQUAL_INT( 0, game.board.stoneCounts[1] );

    takeStone(
        &game,
        0
    );

    TEST_ASSERT_EQUAL_INT( getReservesRegular( 5 ), game.reserves.regular[PLAYER_WHITE] );
    TEST_ASSERT_EQUAL_INT( 0, game.board.stoneCounts[0] );
}

void testLiftStack( void )
{
    Game game = newGame( 3 );

    game.board.stackTypes[0] = STONE_TYPE_CAP;
    game.board.stoneCounts[0] = 4;
    game.board.stoneIds[0] = PLAYER_WHITE;
    game.board.stoneIds[1] = PLAYER_BLACK;
    game.board.stoneIds[2] = PLAYER_WHITE;
    game.board.stoneIds[3] = PLAYER_BLACK;

    liftStack(
        &game,
        0
    );

    TEST_ASSERT_EQUAL_INT( STONE_TYPE_CAP, game.stackBuffer.stoneType );
    TEST_ASSERT_EQUAL_INT( 3, game.stackBuffer.stoneCount );
    TEST_ASSERT_EQUAL_INT( PLAYER_BLACK, game.stackBuffer.stoneIds[0] );
    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, game.stackBuffer.stoneIds[1] );
    TEST_ASSERT_EQUAL_INT( PLAYER_BLACK, game.stackBuffer.stoneIds[2] );

    TEST_ASSERT_EQUAL_INT( STONE_TYPE_FLAT, game.board.stackTypes[0] );
    TEST_ASSERT_EQUAL_INT( 1, game.board.stoneCounts[0] );
    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, game.board.stoneIds[0] );
}

void testDropStack( void )
{
    Game game = newGame( 3 );

    game.board.stackTypes[0] = STONE_TYPE_CAP;
    game.board.stoneCounts[0] = 4;
    game.board.stoneIds[0] = PLAYER_WHITE;
    game.board.stoneIds[1] = PLAYER_BLACK;
    game.board.stoneIds[2] = PLAYER_WHITE;
    game.board.stoneIds[3] = PLAYER_BLACK;

    liftStack(
        &game,
        0
    );

    dropStack(
        &game,
        0
    );

    TEST_ASSERT_EQUAL_INT( 0, game.stackBuffer.stoneCount );

    TEST_ASSERT_EQUAL_INT( STONE_TYPE_CAP, game.board.stackTypes[0] );
    TEST_ASSERT_EQUAL_INT( 4, game.board.stoneCounts[0] );
    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, game.board.stoneIds[0] );
    TEST_ASSERT_EQUAL_INT( PLAYER_BLACK, game.board.stoneIds[1] );
    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, game.board.stoneIds[2] );
    TEST_ASSERT_EQUAL_INT( PLAYER_BLACK, game.board.stoneIds[3] );
}

void testDropStone( void )
{
    Game game = newGame( 3 );

    game.board.stackTypes[0] = STONE_TYPE_FLAT;
    game.board.stoneCounts[0] = 1;
    game.board.stoneIds[0] = PLAYER_WHITE;

    game.stackBuffer.stoneType = STONE_TYPE_STANDING;
    game.stackBuffer.stoneCount = 2;
    game.stackBuffer.stoneIds[0] = PLAYER_WHITE;
    game.stackBuffer.stoneIds[1] = PLAYER_BLACK;

    dropStone(
        &game,
        0
    );

    TEST_ASSERT_EQUAL_INT( STONE_TYPE_FLAT, game.board.stackTypes[0] );
    TEST_ASSERT_EQUAL_INT( 2, game.board.stoneCounts[0] );
    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, game.board.stoneIds[0] );
    TEST_ASSERT_EQUAL_INT( PLAYER_BLACK, game.board.stoneIds[1] );

    dropStone(
        &game,
        0
    );

    TEST_ASSERT_EQUAL_INT( STONE_TYPE_STANDING, game.board.stackTypes[0] );
    TEST_ASSERT_EQUAL_INT( 3, game.board.stoneCounts[0] );
    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, game.board.stoneIds[0] );
    TEST_ASSERT_EQUAL_INT( PLAYER_BLACK, game.board.stoneIds[1] );
    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, game.board.stoneIds[2] );

    game.board.stackTypes[1] = STONE_TYPE_STANDING;
    game.board.stoneCounts[1] = 1;
    game.board.stoneIds[20] = PLAYER_WHITE;

    game.stackBuffer.stoneType = STONE_TYPE_CAP;
    game.stackBuffer.stoneCount = 1;
    game.stackBuffer.stoneIds[0] = PLAYER_BLACK;

    dropStone(
        &game,
        1
    );

    TEST_ASSERT_EQUAL_INT( STONE_TYPE_CAP, game.board.stackTypes[1] );
    TEST_ASSERT_EQUAL_INT( 2, game.board.stoneCounts[1] );
    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, game.board.stoneIds[20] );
    TEST_ASSERT_EQUAL_INT( PLAYER_BLACK, game.board.stoneIds[21] );

    TEST_ASSERT_EQUAL_INT( PLAYER_NONE, game.board.stoneIds[19] );
}

void testLiftStone( void )
{
    Game game = newGame( 3 );

    game.stackBuffer.stoneCount = 2;
    game.stackBuffer.stoneType = STONE_TYPE_CAP;
    game.stackBuffer.stoneIds[0] = PLAYER_WHITE;
    game.stackBuffer.stoneIds[1] = PLAYER_BLACK;

    dropStone(
        &game,
        0
    );

    dropStone(
        &game,
        0
    );

    liftStone(
        &game,
        0,
        true
    );

    TEST_ASSERT_EQUAL_INT( 1, game.stackBuffer.stoneCount );
    TEST_ASSERT_EQUAL_INT( STONE_TYPE_CAP, game.stackBuffer.stoneType );
    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, game.stackBuffer.stoneIds[0] );
    TEST_ASSERT_EQUAL_INT( STONE_TYPE_STANDING, game.board.stackTypes[0] );

    liftStone(
        &game,
        0,
        false
    );

    TEST_ASSERT_EQUAL_INT( 2, game.stackBuffer.stoneCount );
    TEST_ASSERT_EQUAL_INT( STONE_TYPE_CAP, game.stackBuffer.stoneType );
    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, game.stackBuffer.stoneIds[0] );
    TEST_ASSERT_EQUAL_INT( PLAYER_BLACK, game.stackBuffer.stoneIds[1] );
}

#endif
