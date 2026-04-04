#ifndef IG20260327191049
#define IG20260327191049

#include "App.h"
#include "AppSystem.h"
#include "GameConstants.h"
#include "GameSystem.h"
#include "InputId.h"
#include <unity.h>

void testNewApp( void )
{
    App app = newApp( 0 );

    TEST_ASSERT_EQUAL_INT( BOARD_WIDTH_DEFAULT, app.game.board.width );
    TEST_ASSERT_EQUAL_INT( INPUT_NONE, app.inputBuffer.keyboard );
    TEST_ASSERT_EQUAL_INT( false, app.shouldClose );

    app = newApp( 3 );

    TEST_ASSERT_EQUAL_INT( 3, app.game.board.width );

    app = newApp( 8 );

    TEST_ASSERT_EQUAL_INT( 8, app.game.board.width );
}

void testUndo( void )
{
    App app = newApp( 5 );

    placeStone(
        &app.game,
        PLAYER_WHITE,
        FILE_A,
        RANK_1,
        STONE_TYPE_FLAT
    );

    placeStone(
        &app.game,
        PLAYER_WHITE,
        FILE_B,
        RANK_1,
        STONE_TYPE_STANDING
    );

    placeStone(
        &app.game,
        PLAYER_WHITE,
        FILE_C,
        RANK_1,
        STONE_TYPE_CAP
    );

    liftStack(
        &app.game,
        FILE_A,
        RANK_1
    );

    dropStone(
        &app.game,
        FILE_D,
        RANK_1
    );

    undo( &app );

    TEST_ASSERT_EQUAL_INT( 1, app.game.stackBuffer.stoneCount );
    TEST_ASSERT_EQUAL_INT( 0, app.game.board.stoneCounts[3] );

    undo( &app );

    TEST_ASSERT_EQUAL_INT( 0, app.game.stackBuffer.stoneCount );
    TEST_ASSERT_EQUAL_INT( 1, app.game.board.stoneCounts[0] );

    undo( &app );

    TEST_ASSERT_EQUAL_INT( 1, app.game.reserves.capstone[PLAYER_WHITE] );
    TEST_ASSERT_EQUAL_INT( 0, app.game.board.stoneCounts[2] );

    undo( &app );

    TEST_ASSERT_EQUAL_INT( 20, app.game.reserves.regular[PLAYER_WHITE] );
    TEST_ASSERT_EQUAL_INT( 0, app.game.board.stoneCounts[1] );

    undo( &app );

    TEST_ASSERT_EQUAL_INT( 21, app.game.reserves.regular[PLAYER_WHITE] );
    TEST_ASSERT_EQUAL_INT( 0, app.game.board.stoneCounts[0] );
}

void testRedo( void )
{
    App app = newApp( 5 );

    placeStone(
        &app.game,
        PLAYER_WHITE,
        FILE_A,
        RANK_1,
        STONE_TYPE_FLAT
    );

    placeStone(
        &app.game,
        PLAYER_WHITE,
        FILE_B,
        RANK_1,
        STONE_TYPE_STANDING
    );

    placeStone(
        &app.game,
        PLAYER_WHITE,
        FILE_C,
        RANK_1,
        STONE_TYPE_CAP
    );

    liftStack(
        &app.game,
        FILE_A,
        RANK_1
    );

    dropStone(
        &app.game,
        FILE_D,
        RANK_1
    );

    undo( &app );
    undo( &app );
    undo( &app );
    undo( &app );
    undo( &app );

    redo( &app );

    TEST_ASSERT_EQUAL_INT( 20, app.game.reserves.regular[PLAYER_WHITE] );
    TEST_ASSERT_EQUAL_INT( 1, app.game.board.stoneCounts[0] );

    redo( &app );

    TEST_ASSERT_EQUAL_INT( 19, app.game.reserves.regular[PLAYER_WHITE] );
    TEST_ASSERT_EQUAL_INT( 1, app.game.board.stoneCounts[1] );

    redo( &app );

    TEST_ASSERT_EQUAL_INT( 0, app.game.reserves.capstone[PLAYER_WHITE] );
    TEST_ASSERT_EQUAL_INT( 1, app.game.board.stoneCounts[2] );

    redo( &app );

    TEST_ASSERT_EQUAL_INT( 1, app.game.stackBuffer.stoneCount );
    TEST_ASSERT_EQUAL_INT( 0, app.game.board.stoneCounts[0] );

    redo( &app );

    TEST_ASSERT_EQUAL_INT( 0, app.game.stackBuffer.stoneCount );
    TEST_ASSERT_EQUAL_INT( 1, app.game.board.stoneCounts[3] );
}

#endif
