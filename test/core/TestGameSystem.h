#ifndef IG20260117152251
#define IG20260117152251

#include "FileId.h"
#include "Game.h"
#include "GameSystem.h"
#include "PlayerId.h"
#include "RankId.h"
#include "StoneTypeId.h"
#include "unity.h"

void testNewGame( void )
{
    Game game0 = newGame( 0 );

    TEST_ASSERT_EQUAL_INT( BOARD_WIDTH_DEFAULT, game0.board.width );

    Game game3 = newGame( 3 );

    TEST_ASSERT_EQUAL_INT( 3, game3.board.width );

    Game game8 = newGame( 8 );

    TEST_ASSERT_EQUAL_INT( 8, game8.board.width );
}

void testPlaceStone( void )
{
    Game game = newGame( 5 );

    placeStone(
        &game,
        PLAYER_WHITE,
        FILE_A,
        RANK_1,
        STONE_TYPE_FLAT
    );

    TEST_ASSERT_EQUAL_INT( 20, game.players.reservesRegular[PLAYER_WHITE] );
    TEST_ASSERT_EQUAL_INT( 1, game.board.stoneCounts[0] );
    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, game.board.stoneIds[0] );
    TEST_ASSERT_EQUAL_INT( PLAYER_NONE, game.board.stoneIds[1] );
    TEST_ASSERT_EQUAL_INT( STONE_TYPE_FLAT, game.board.types[0] );

    placeStone(
        &game,
        PLAYER_BLACK,
        FILE_B,
        RANK_1,
        STONE_TYPE_STANDING
    );

    TEST_ASSERT_EQUAL_INT( 20, game.players.reservesRegular[PLAYER_BLACK] );
    TEST_ASSERT_EQUAL_INT( 1, game.board.stoneCounts[1] );
    TEST_ASSERT_EQUAL_INT( PLAYER_BLACK, game.board.stoneIds[1 * 43] );
    TEST_ASSERT_EQUAL_INT( PLAYER_NONE, game.board.stoneIds[1] );
    TEST_ASSERT_EQUAL_INT( STONE_TYPE_STANDING, game.board.types[1] );

    placeStone(
        &game,
        PLAYER_WHITE,
        FILE_C,
        RANK_1,
        STONE_TYPE_CAP
    );

    TEST_ASSERT_EQUAL_INT( 0, game.players.reservesCapstone[PLAYER_WHITE] );
    TEST_ASSERT_EQUAL_INT( 1, game.board.stoneCounts[2] );
    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, game.board.stoneIds[2 * 43] );
    TEST_ASSERT_EQUAL_INT( PLAYER_NONE, game.board.stoneIds[2 * 43 + 1] );
    TEST_ASSERT_EQUAL_INT( STONE_TYPE_CAP, game.board.types[2] );
}

void testUndoPlaceStone( void )
{
    Game game = newGame( 5 );

    placeStone(
        &game,
        PLAYER_WHITE,
        FILE_A,
        RANK_1,
        STONE_TYPE_FLAT
    );

    placeStone(
        &game,
        PLAYER_WHITE,
        FILE_B,
        RANK_1,
        STONE_TYPE_STANDING
    );

    placeStone(
        &game,
        PLAYER_WHITE,
        FILE_C,
        RANK_1,
        STONE_TYPE_CAP
    );

    undoPlaceStone( &game );

    TEST_ASSERT_EQUAL_INT( 1, game.players.reservesCapstone[PLAYER_WHITE] );
    TEST_ASSERT_EQUAL_INT( 0, game.board.stoneCounts[2] );

    undoPlaceStone( &game );

    TEST_ASSERT_EQUAL_INT( 20, game.players.reservesRegular[PLAYER_WHITE] );
    TEST_ASSERT_EQUAL_INT( 0, game.board.stoneCounts[1] );

    undoPlaceStone( &game );

    TEST_ASSERT_EQUAL_INT( 21, game.players.reservesRegular[PLAYER_WHITE] );
    TEST_ASSERT_EQUAL_INT( 0, game.board.stoneCounts[0] );
}

void testRedoPlaceStone( void )
{
    Game game = newGame( 5 );

    placeStone(
        &game,
        PLAYER_WHITE,
        FILE_A,
        RANK_1,
        STONE_TYPE_CAP
    );

    undoPlaceStone( &game );
    redoPlaceStone( &game );

    TEST_ASSERT_EQUAL_INT( 0, game.players.reservesCapstone[PLAYER_WHITE] );
    TEST_ASSERT_EQUAL_INT( 1, game.board.stoneCounts[0] );
}

void testLiftStack( void )
{
    Game game = newGame( 3 );

    game.board.types[0] = STONE_TYPE_CAP;
    game.board.stoneCounts[0] = 4;
    game.board.stoneIds[0] = PLAYER_WHITE;
    game.board.stoneIds[1] = PLAYER_BLACK;
    game.board.stoneIds[2] = PLAYER_WHITE;
    game.board.stoneIds[3] = PLAYER_BLACK;

    liftStack(
        &game,
        FILE_A,
        RANK_1
    );

    TEST_ASSERT_EQUAL_INT( STONE_TYPE_CAP, game.stackBuffer.stoneType );
    TEST_ASSERT_EQUAL_INT( 3, game.stackBuffer.stoneCount );
    TEST_ASSERT_EQUAL_INT( PLAYER_BLACK, game.stackBuffer.stoneIds[0] );
    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, game.stackBuffer.stoneIds[1] );
    TEST_ASSERT_EQUAL_INT( PLAYER_BLACK, game.stackBuffer.stoneIds[2] );

    TEST_ASSERT_EQUAL_INT( STONE_TYPE_FLAT, game.board.types[0] );
    TEST_ASSERT_EQUAL_INT( 1, game.board.stoneCounts[0] );
    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, game.board.stoneIds[0] );
}

void testUndoLiftStack( void )
{
    Game game = newGame( 3 );

    game.board.types[0] = STONE_TYPE_CAP;
    game.board.stoneCounts[0] = 4;
    game.board.stoneIds[0] = PLAYER_WHITE;
    game.board.stoneIds[1] = PLAYER_BLACK;
    game.board.stoneIds[2] = PLAYER_WHITE;
    game.board.stoneIds[3] = PLAYER_BLACK;

    liftStack(
        &game,
        FILE_A,
        RANK_1
    );

    undoLiftStack( &game );

    TEST_ASSERT_EQUAL_INT( 0, game.stackBuffer.stoneCount );

    TEST_ASSERT_EQUAL_INT( STONE_TYPE_CAP, game.board.types[0] );
    TEST_ASSERT_EQUAL_INT( 4, game.board.stoneCounts[0] );
    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, game.board.stoneIds[0] );
    TEST_ASSERT_EQUAL_INT( PLAYER_BLACK, game.board.stoneIds[1] );
    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, game.board.stoneIds[2] );
    TEST_ASSERT_EQUAL_INT( PLAYER_BLACK, game.board.stoneIds[3] );
}

void testRedoLiftStack( void )
{
    Game game = newGame( 3 );

    game.board.types[0] = STONE_TYPE_CAP;
    game.board.stoneCounts[0] = 4;
    game.board.stoneIds[0] = PLAYER_WHITE;
    game.board.stoneIds[1] = PLAYER_BLACK;
    game.board.stoneIds[2] = PLAYER_WHITE;
    game.board.stoneIds[3] = PLAYER_BLACK;

    liftStack(
        &game,
        FILE_A,
        RANK_1
    );

    undoLiftStack( &game );
    redoLiftStack( &game );

    TEST_ASSERT_EQUAL_INT( STONE_TYPE_CAP, game.stackBuffer.stoneType );
    TEST_ASSERT_EQUAL_INT( 3, game.stackBuffer.stoneCount );
    TEST_ASSERT_EQUAL_INT( PLAYER_BLACK, game.stackBuffer.stoneIds[0] );
    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, game.stackBuffer.stoneIds[1] );
    TEST_ASSERT_EQUAL_INT( PLAYER_BLACK, game.stackBuffer.stoneIds[2] );

    TEST_ASSERT_EQUAL_INT( STONE_TYPE_FLAT, game.board.types[0] );
    TEST_ASSERT_EQUAL_INT( 1, game.board.stoneCounts[0] );
    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, game.board.stoneIds[0] );
}

void testDropStone( void )
{
    Game game = newGame( 3 );

    game.board.types[0] = STONE_TYPE_FLAT;
    game.board.stoneCounts[0] = 1;
    game.board.stoneIds[0] = PLAYER_WHITE;

    game.stackBuffer.stoneType = STONE_TYPE_STANDING;
    game.stackBuffer.stoneCount = 2;
    game.stackBuffer.stoneIds[0] = PLAYER_WHITE;
    game.stackBuffer.stoneIds[1] = PLAYER_BLACK;

    dropStone(
        &game,
        FILE_A,
        RANK_1
    );

    TEST_ASSERT_EQUAL_INT( STONE_TYPE_FLAT, game.board.types[0] );
    TEST_ASSERT_EQUAL_INT( 2, game.board.stoneCounts[0] );
    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, game.board.stoneIds[0] );
    TEST_ASSERT_EQUAL_INT( PLAYER_BLACK, game.board.stoneIds[1] );

    dropStone(
        &game,
        FILE_A,
        RANK_1
    );

    TEST_ASSERT_EQUAL_INT( STONE_TYPE_STANDING, game.board.types[0] );
    TEST_ASSERT_EQUAL_INT( 3, game.board.stoneCounts[0] );
    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, game.board.stoneIds[0] );
    TEST_ASSERT_EQUAL_INT( PLAYER_BLACK, game.board.stoneIds[1] );
    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, game.board.stoneIds[2] );

    game.board.types[1] = STONE_TYPE_STANDING;
    game.board.stoneCounts[1] = 1;
    game.board.stoneIds[20] = PLAYER_WHITE;

    game.stackBuffer.stoneType = STONE_TYPE_CAP;
    game.stackBuffer.stoneCount = 1;
    game.stackBuffer.stoneIds[0] = PLAYER_BLACK;

    dropStone(
        &game,
        FILE_B,
        RANK_1
    );

    TEST_ASSERT_EQUAL_INT( STONE_TYPE_CAP, game.board.types[1] );
    TEST_ASSERT_EQUAL_INT( 2, game.board.stoneCounts[1] );
    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, game.board.stoneIds[20] );
    TEST_ASSERT_EQUAL_INT( PLAYER_BLACK, game.board.stoneIds[21] );
}

void testUndo( void )
{
    Game game = newGame( 5 );

    placeStone(
        &game,
        PLAYER_WHITE,
        FILE_A,
        RANK_1,
        STONE_TYPE_FLAT
    );

    placeStone(
        &game,
        PLAYER_WHITE,
        FILE_B,
        RANK_1,
        STONE_TYPE_STANDING
    );

    placeStone(
        &game,
        PLAYER_WHITE,
        FILE_C,
        RANK_1,
        STONE_TYPE_CAP
    );

    liftStack(
        &game,
        FILE_A,
        RANK_1
    );

    dropStone(
        &game,
        FILE_D,
        RANK_1
    );

    undo( &game );

    TEST_ASSERT_EQUAL_INT( 1, game.stackBuffer.stoneCount );
    TEST_ASSERT_EQUAL_INT( 0, game.board.stoneCounts[3] );

    undo( &game );

    TEST_ASSERT_EQUAL_INT( 0, game.stackBuffer.stoneCount );
    TEST_ASSERT_EQUAL_INT( 1, game.board.stoneCounts[0] );

    undo( &game );

    TEST_ASSERT_EQUAL_INT( 1, game.players.reservesCapstone[PLAYER_WHITE] );
    TEST_ASSERT_EQUAL_INT( 0, game.board.stoneCounts[2] );

    undo( &game );

    TEST_ASSERT_EQUAL_INT( 20, game.players.reservesRegular[PLAYER_WHITE] );
    TEST_ASSERT_EQUAL_INT( 0, game.board.stoneCounts[1] );

    undo( &game );

    TEST_ASSERT_EQUAL_INT( 21, game.players.reservesRegular[PLAYER_WHITE] );
    TEST_ASSERT_EQUAL_INT( 0, game.board.stoneCounts[0] );
}

void testRedo( void )
{
    Game game = newGame( 5 );

    placeStone(
        &game,
        PLAYER_WHITE,
        FILE_A,
        RANK_1,
        STONE_TYPE_FLAT
    );

    placeStone(
        &game,
        PLAYER_WHITE,
        FILE_B,
        RANK_1,
        STONE_TYPE_STANDING
    );

    placeStone(
        &game,
        PLAYER_WHITE,
        FILE_C,
        RANK_1,
        STONE_TYPE_CAP
    );

    liftStack(
        &game,
        FILE_A,
        RANK_1
    );

    dropStone(
        &game,
        FILE_D,
        RANK_1
    );

    undo( &game );
    undo( &game );
    undo( &game );
    undo( &game );
    undo( &game );

    redo( &game );

    TEST_ASSERT_EQUAL_INT( 20, game.players.reservesRegular[PLAYER_WHITE] );
    TEST_ASSERT_EQUAL_INT( 1, game.board.stoneCounts[0] );

    redo( &game );

    TEST_ASSERT_EQUAL_INT( 19, game.players.reservesRegular[PLAYER_WHITE] );
    TEST_ASSERT_EQUAL_INT( 1, game.board.stoneCounts[1] );

    redo( &game );

    TEST_ASSERT_EQUAL_INT( 0, game.players.reservesCapstone[PLAYER_WHITE] );
    TEST_ASSERT_EQUAL_INT( 1, game.board.stoneCounts[2] );

    redo( &game );

    TEST_ASSERT_EQUAL_INT( 1, game.stackBuffer.stoneCount );
    TEST_ASSERT_EQUAL_INT( 0, game.board.stoneCounts[0] );

    redo( &game );

    TEST_ASSERT_EQUAL_INT( 0, game.stackBuffer.stoneCount );
    TEST_ASSERT_EQUAL_INT( 1, game.board.stoneCounts[3] );
}
#endif
