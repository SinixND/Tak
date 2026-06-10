#ifndef IG20260117152251
#define IG20260117152251

#include "Board.h"
#include "Game.h"
#include "GameConstants.h"
#include "PlayerId.h"
#include "StoneTypeId.h"
#include "unity.h"

void testPlaceStone( void )
{
    Game game = newGame( 5 );

    placeStone(
        &game,
        PLAYER_WHITE,
        6,
        STONE_TYPE_FLAT
    );

    TEST_ASSERT_EQUAL_INT( getReservesRegular( 5 ) - 1, game.reserves.regular[PLAYER_WHITE] );
    TEST_ASSERT_EQUAL_INT( 1, game.board.stoneCounts[6] );
    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, game.board.stoneIds[6 * getStackCapacity( 5 )] );
    TEST_ASSERT_EQUAL_INT( PLAYER_NONE, game.board.stoneIds[6 * getStackCapacity( 5 ) + 1] );
    TEST_ASSERT_EQUAL_INT( STONE_TYPE_FLAT, game.board.stackTypes[6] );

    placeStone(
        &game,
        PLAYER_BLACK,
        1,
        STONE_TYPE_STANDING
    );

    TEST_ASSERT_EQUAL_INT( getReservesRegular( 5 ) - 1, game.reserves.regular[PLAYER_BLACK] );
    TEST_ASSERT_EQUAL_INT( 1, game.board.stoneCounts[1] );
    TEST_ASSERT_EQUAL_INT( PLAYER_BLACK, game.board.stoneIds[1 * getStackCapacity( 5 )] );
    TEST_ASSERT_EQUAL_INT( PLAYER_NONE, game.board.stoneIds[1 * getStackCapacity( 5 ) + 1] );
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
        6,
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
        6
    );

    TEST_ASSERT_EQUAL_INT( getReservesRegular( 5 ), game.reserves.regular[PLAYER_WHITE] );
    TEST_ASSERT_EQUAL_INT( 0, game.board.stoneCounts[6] );
}

void testLiftStack( void )
{
    Game game = newGame( 3 );

    game.board.stackTypes[6] = STONE_TYPE_CAP;
    game.board.stoneCounts[6] = 4;
    game.board.stoneIds[6 * getStackCapacity( 3 )] = PLAYER_WHITE;
    game.board.stoneIds[6 * getStackCapacity( 3 ) + 1] = PLAYER_BLACK;
    game.board.stoneIds[6 * getStackCapacity( 3 ) + 2] = PLAYER_WHITE;
    game.board.stoneIds[6 * getStackCapacity( 3 ) + 3] = PLAYER_BLACK;
    game.board.stackIds[6] = PLAYER_BLACK;

    liftStack(
        &game,
        6
    );

    TEST_ASSERT_EQUAL_INT( STONE_TYPE_CAP, game.stackBuffer.stackType );
    TEST_ASSERT_EQUAL_INT( 3, game.stackBuffer.stoneCount );
    TEST_ASSERT_EQUAL_INT( PLAYER_BLACK, game.stackBuffer.stoneIds[0] );
    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, game.stackBuffer.stoneIds[1] );
    TEST_ASSERT_EQUAL_INT( PLAYER_BLACK, game.stackBuffer.stoneIds[2] );

    TEST_ASSERT_EQUAL_INT( STONE_TYPE_FLAT, game.board.stackTypes[6] );
    TEST_ASSERT_EQUAL_INT( 1, game.board.stoneCounts[6] );
    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, game.board.stoneIds[6 * getStackCapacity( 3 )] );
    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, game.board.stackIds[6] );
}

void testDropStack( void )
{
    Game game = newGame( 3 );

    game.board.stackTypes[6] = STONE_TYPE_CAP;
    game.board.stoneCounts[6] = 4;
    game.board.stoneIds[6 * getStackCapacity( 3 )] = PLAYER_WHITE;
    game.board.stoneIds[6 * getStackCapacity( 3 ) + 1] = PLAYER_BLACK;
    game.board.stoneIds[6 * getStackCapacity( 3 ) + 2] = PLAYER_WHITE;
    game.board.stoneIds[6 * getStackCapacity( 3 ) + 3] = PLAYER_BLACK;
    game.board.stackIds[6] = PLAYER_BLACK;

    liftStack(
        &game,
        6
    );

    dropStack(
        &game,
        6
    );

    TEST_ASSERT_EQUAL_INT( 0, game.stackBuffer.stoneCount );

    TEST_ASSERT_EQUAL_INT( STONE_TYPE_CAP, game.board.stackTypes[6] );
    TEST_ASSERT_EQUAL_INT( 4, game.board.stoneCounts[6] );
    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, game.board.stoneIds[6 * getStackCapacity( 3 )] );
    TEST_ASSERT_EQUAL_INT( PLAYER_BLACK, game.board.stoneIds[6 * getStackCapacity( 3 ) + 1] );
    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, game.board.stoneIds[6 * getStackCapacity( 3 ) + 2] );
    TEST_ASSERT_EQUAL_INT( PLAYER_BLACK, game.board.stoneIds[6 * getStackCapacity( 3 ) + 3] );
    TEST_ASSERT_EQUAL_INT( PLAYER_BLACK, game.board.stackIds[6] );
}

void testDropStone( void )
{
    Game game = newGame( 3 );

    game.board.stackTypes[6] = STONE_TYPE_FLAT;
    game.board.stoneCounts[6] = 1;
    game.board.stoneIds[6 * getStackCapacity( 3 )] = PLAYER_WHITE;

    game.stackBuffer.stackType = STONE_TYPE_STANDING;
    game.stackBuffer.stoneCount = 2;
    game.stackBuffer.stoneIds[0] = PLAYER_WHITE;
    game.stackBuffer.stoneIds[1] = PLAYER_BLACK;

    dropStone(
        &game,
        6
    );

    TEST_ASSERT_EQUAL_INT( STONE_TYPE_FLAT, game.board.stackTypes[6] );
    TEST_ASSERT_EQUAL_INT( 2, game.board.stoneCounts[6] );
    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, game.board.stoneIds[6 * getStackCapacity( 3 )] );
    TEST_ASSERT_EQUAL_INT( PLAYER_BLACK, game.board.stoneIds[6 * getStackCapacity( 3 ) + 1] );

    dropStone(
        &game,
        6
    );

    TEST_ASSERT_EQUAL_INT( STONE_TYPE_STANDING, game.board.stackTypes[6] );
    TEST_ASSERT_EQUAL_INT( 3, game.board.stoneCounts[6] );
    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, game.board.stoneIds[6 * getStackCapacity( 3 )] );
    TEST_ASSERT_EQUAL_INT( PLAYER_BLACK, game.board.stoneIds[6 * getStackCapacity( 3 ) + 1] );
    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, game.board.stoneIds[6 * getStackCapacity( 3 ) + 2] );

    game.board.stackTypes[1] = STONE_TYPE_STANDING;
    game.board.stoneCounts[1] = 1;
    game.board.stoneIds[1 * getStackCapacity( 3 )] = PLAYER_WHITE;

    game.stackBuffer.stackType = STONE_TYPE_CAP;
    game.stackBuffer.stoneCount = 1;
    game.stackBuffer.stoneIds[0] = PLAYER_BLACK;

    dropStone(
        &game,
        1
    );

    TEST_ASSERT_EQUAL_INT( STONE_TYPE_CAP, game.board.stackTypes[1] );
    TEST_ASSERT_EQUAL_INT( 2, game.board.stoneCounts[1] );
    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, game.board.stoneIds[1 * getStackCapacity( 3 )] );
    TEST_ASSERT_EQUAL_INT( PLAYER_BLACK, game.board.stoneIds[1 * getStackCapacity( 3 ) + 1] );

    TEST_ASSERT_EQUAL_INT( PLAYER_NONE, game.board.stoneIds[1 * getStackCapacity( 3 ) - 1] );
}

void testLiftStone( void )
{
    Game game = newGame( 3 );

    game.stackBuffer.stoneCount = 2;
    game.stackBuffer.stackType = STONE_TYPE_CAP;
    game.stackBuffer.stoneIds[0] = PLAYER_WHITE;
    game.stackBuffer.stoneIds[1] = PLAYER_BLACK;

    dropStone(
        &game,
        6
    );

    dropStone(
        &game,
        6
    );

    game.stackBuffer.stackType = STONE_TYPE_NONE;

    liftStone(
        &game,
        6,
        true
    );

    TEST_ASSERT_EQUAL_INT( 1, game.stackBuffer.stoneCount );
    TEST_ASSERT_EQUAL_INT( STONE_TYPE_CAP, game.stackBuffer.stackType );
    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, game.stackBuffer.stoneIds[0] );
    TEST_ASSERT_EQUAL_INT( STONE_TYPE_STANDING, game.board.stackTypes[6] );

    liftStone(
        &game,
        6,
        false
    );

    TEST_ASSERT_EQUAL_INT( 2, game.stackBuffer.stoneCount );
    TEST_ASSERT_EQUAL_INT( STONE_TYPE_CAP, game.stackBuffer.stackType );
    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, game.stackBuffer.stoneIds[0] );
    TEST_ASSERT_EQUAL_INT( PLAYER_BLACK, game.stackBuffer.stoneIds[1] );
}

void testExecuteEvent( void )
{
    Event event = newEvent();
    Game game = newGame( 5 );

    event.actionType = ACTION_TYPE_PLACE;
    event.playerId = PLAYER_WHITE;
    event.squareIdx = 6;
    event.stoneType = STONE_TYPE_STANDING;

    executeEvent( &game, &event );

    TEST_ASSERT_EQUAL_INT( getReservesRegular( 5 ) - 1, game.reserves.regular[PLAYER_WHITE] );
    TEST_ASSERT_EQUAL_INT( getReservesCapstone( 5 ), game.board.stoneCounts[6] );
    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, game.board.stoneIds[6 * getStackCapacity( 5 )] );
    TEST_ASSERT_EQUAL_INT( PLAYER_NONE, game.board.stoneIds[6 * getStackCapacity( 5 ) + 1] );
    TEST_ASSERT_EQUAL_INT( STONE_TYPE_STANDING, game.board.stackTypes[6] );

    event.actionType = ACTION_TYPE_LIFT;

    executeEvent( &game, &event );

    TEST_ASSERT_EQUAL_INT( STONE_TYPE_STANDING, game.stackBuffer.stackType );
    TEST_ASSERT_EQUAL_INT( 1, game.stackBuffer.stoneCount );
    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, game.stackBuffer.stoneIds[0] );

    TEST_ASSERT_EQUAL_INT( 0, game.board.stoneCounts[6] );

    event.actionType = ACTION_TYPE_DROP;
    event.dropCount = 1;

    executeEvent( &game, &event );

    TEST_ASSERT_EQUAL_INT( STONE_TYPE_STANDING, game.board.stackTypes[6] );
    TEST_ASSERT_EQUAL_INT( 1, game.board.stoneCounts[6] );
    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, game.board.stoneIds[258] );
}

void testUpdateScore( void )
{
    Game game = newGame( 3 );

    game.board.stackIds[0] = PLAYER_BLACK;
    game.board.stackIds[1] = PLAYER_BLACK;
    game.board.stackIds[2] = PLAYER_BLACK;
    game.board.stackIds[3] = PLAYER_WHITE;
    game.board.stackIds[4] = PLAYER_WHITE;
    game.board.stackIds[7] = PLAYER_WHITE;

    game.board.stackTypes[0] = STONE_TYPE_FLAT;
    game.board.stackTypes[1] = STONE_TYPE_FLAT;
    game.board.stackTypes[2] = STONE_TYPE_FLAT;
    game.board.stackTypes[3] = STONE_TYPE_FLAT;
    game.board.stackTypes[4] = STONE_TYPE_FLAT;
    game.board.stackTypes[7] = STONE_TYPE_FLAT;

    updateScore( &game );
    TEST_ASSERT_EQUAL_INT( 3, game.scores[PLAYER_WHITE] );
    TEST_ASSERT_EQUAL_INT( 3, game.scores[PLAYER_BLACK] );

    game.board.stackIds[8] = PLAYER_WHITE;
    game.board.stackTypes[8] = STONE_TYPE_CAP;
    updateScore( &game );
    TEST_ASSERT_EQUAL_INT( 3, game.scores[PLAYER_WHITE] );

    game.board.stackTypes[8] = STONE_TYPE_FLAT;
    updateScore( &game );
    TEST_ASSERT_EQUAL_INT( 4, game.scores[PLAYER_WHITE] );
}

#endif
