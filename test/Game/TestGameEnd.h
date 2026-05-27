#ifndef IG20260515154201
#define IG20260515154201

#include "Board.h"
#include "FileId.h"
#include "Game.h"
#include "GameConstants.h"
#include "GameEnd.h"
#include "PathSquare.h"
#include "PlayerId.h"
#include "RankId.h"
#include "Reserves.h"
#include "StoneTypeId.h"
#include <unity.h>

void testAreReservesExhausted( void )
{
    Reserves reserves = newReserves( 3 );

    TEST_ASSERT_EQUAL_INT( false, areReservesExhausted( &reserves, PLAYER_WHITE ) );
    TEST_ASSERT_EQUAL_INT( false, areReservesExhausted( &reserves, PLAYER_BLACK ) );

    reserves.regular[PLAYER_BLACK] = 0;
    TEST_ASSERT_EQUAL_INT( false, areReservesExhausted( &reserves, PLAYER_WHITE ) );
    TEST_ASSERT_EQUAL_INT( true, areReservesExhausted( &reserves, PLAYER_BLACK ) );

    reserves = newReserves( 5 );
    TEST_ASSERT_EQUAL_INT( false, areReservesExhausted( &reserves, PLAYER_WHITE ) );
    TEST_ASSERT_EQUAL_INT( false, areReservesExhausted( &reserves, PLAYER_BLACK ) );

    reserves.regular[PLAYER_BLACK] = 0;
    TEST_ASSERT_EQUAL_INT( false, areReservesExhausted( &reserves, PLAYER_WHITE ) );
    TEST_ASSERT_EQUAL_INT( false, areReservesExhausted( &reserves, PLAYER_BLACK ) );

    reserves.capstone[PLAYER_BLACK] = 0;
    TEST_ASSERT_EQUAL_INT( false, areReservesExhausted( &reserves, PLAYER_WHITE ) );
    TEST_ASSERT_EQUAL_INT( true, areReservesExhausted( &reserves, PLAYER_BLACK ) );
}

void testIsSquareValid( void )
{
    Board board = newBoard( 3 );
    TEST_ASSERT_EQUAL_INT( false, isSquareValid( &board, 0, PLAYER_BLACK ) );

    board.stackIds[0] = PLAYER_BLACK;
    board.stackTypes[0] = STONE_TYPE_FLAT;
    TEST_ASSERT_EQUAL_INT( true, isSquareValid( &board, 0, PLAYER_BLACK ) );

    board.stackTypes[0] = STONE_TYPE_CAP;
    TEST_ASSERT_EQUAL_INT( true, isSquareValid( &board, 0, PLAYER_BLACK ) );

    board.stackIds[1] = PLAYER_WHITE;
    board.stackTypes[1] = STONE_TYPE_FLAT;
    TEST_ASSERT_EQUAL_INT( true, isSquareValid( &board, 1, PLAYER_WHITE ) );

    board.stackTypes[1] = STONE_TYPE_CAP;
    TEST_ASSERT_EQUAL_INT( true, isSquareValid( &board, 1, PLAYER_WHITE ) );
}

void testInitPathSquares( void )
{
    Game game = newGame( 3 );
    PathSquare pathSquares[SQUARES_MAX];
    resetPathSquares(
        pathSquares,
        game.board.squareCount
    );

    game.board.stackTypes[0] = STONE_TYPE_CAP;
    game.board.stackIds[0] = PLAYER_WHITE;
    game.board.stackTypes[1] = STONE_TYPE_FLAT;
    game.board.stackIds[1] = PLAYER_WHITE;
    game.board.stackTypes[2] = STONE_TYPE_FLAT;
    game.board.stackIds[2] = PLAYER_WHITE;

    game.board.stackTypes[3] = STONE_TYPE_CAP;
    game.board.stackIds[3] = PLAYER_BLACK;
    game.board.stackTypes[4] = STONE_TYPE_FLAT;
    game.board.stackIds[4] = PLAYER_BLACK;
    game.board.stackTypes[7] = STONE_TYPE_FLAT;
    game.board.stackIds[7] = PLAYER_BLACK;
    game.board.stackTypes[8] = STONE_TYPE_FLAT;
    game.board.stackIds[8] = PLAYER_BLACK;

    updatePathSquares( pathSquares, &game.board, PLAYER_WHITE );
    TEST_ASSERT_EQUAL_INT( true, pathSquares[0].isValid );
    TEST_ASSERT_EQUAL_INT( false, pathSquares[0].wasChecked );
    TEST_ASSERT_EQUAL_INT( false, pathSquares[3].isValid );
    TEST_ASSERT_EQUAL_INT( false, pathSquares[3].wasChecked );
    TEST_ASSERT_EQUAL_INT( false, pathSquares[6].isValid );
    TEST_ASSERT_EQUAL_INT( false, pathSquares[6].wasChecked );

    resetPathSquares(
        pathSquares,
        game.board.squareCount
    );

    updatePathSquares( pathSquares, &game.board, PLAYER_BLACK );
    TEST_ASSERT_EQUAL_INT( false, pathSquares[0].isValid );
    TEST_ASSERT_EQUAL_INT( false, pathSquares[0].wasChecked );
    TEST_ASSERT_EQUAL_INT( true, pathSquares[3].isValid );
    TEST_ASSERT_EQUAL_INT( false, pathSquares[3].wasChecked );
}

void testFindVerticalRoad( void )
{
    PathSquare pathSquares[SQUARES_MAX];
    resetPathSquares(
        pathSquares,
        9
    );

    TEST_ASSERT_EQUAL_INT( false, isRoadCompleteVertical( pathSquares, FILE_NONE, RANK_1, 3 ) );

    TEST_ASSERT_EQUAL_INT( false, isRoadCompleteVertical( pathSquares, FILE_A, RANK_1, 3 ) );

    resetPathSquares(
        pathSquares,
        9
    );

    pathSquares[0].isValid = true;
    pathSquares[0].wasChecked = false;
    pathSquares[3].isValid = true;
    pathSquares[3].wasChecked = false;
    pathSquares[4].isValid = true;
    pathSquares[4].wasChecked = false;

    TEST_ASSERT_EQUAL_INT( false, isRoadCompleteVertical( pathSquares, FILE_A, RANK_1, 3 ) );

    resetPathSquares(
        pathSquares,
        9
    );

    pathSquares[0].isValid = true;
    pathSquares[0].wasChecked = false;
    pathSquares[3].isValid = true;
    pathSquares[3].wasChecked = false;
    pathSquares[4].isValid = true;
    pathSquares[4].wasChecked = false;
    pathSquares[7].isValid = true;
    pathSquares[7].wasChecked = false;
    TEST_ASSERT_EQUAL_INT( true, isRoadCompleteVertical( pathSquares, FILE_A, RANK_1, 3 ) );

    TEST_ASSERT_EQUAL_INT( true, pathSquares[0].wasChecked );
    TEST_ASSERT_EQUAL_INT( false, pathSquares[1].wasChecked );
    TEST_ASSERT_EQUAL_INT( false, pathSquares[2].wasChecked );

    TEST_ASSERT_EQUAL_INT( true, pathSquares[3].wasChecked );
    TEST_ASSERT_EQUAL_INT( true, pathSquares[4].wasChecked );
    TEST_ASSERT_EQUAL_INT( false, pathSquares[5].wasChecked );

    TEST_ASSERT_EQUAL_INT( false, pathSquares[6].wasChecked );
    TEST_ASSERT_EQUAL_INT( false, pathSquares[7].wasChecked );
    TEST_ASSERT_EQUAL_INT( false, pathSquares[8].wasChecked );
}

void testFindHorizontalRoad( void )
{
    PathSquare pathSquares[SQUARES_MAX];
    resetPathSquares(
        pathSquares,
        9
    );

    TEST_ASSERT_EQUAL_INT( false, isRoadCompleteHorizontal( pathSquares, FILE_NONE, RANK_1, 3 ) );

    TEST_ASSERT_EQUAL_INT( false, isRoadCompleteHorizontal( pathSquares, FILE_A, RANK_1, 3 ) );

    resetPathSquares(
        pathSquares,
        9
    );

    pathSquares[0].isValid = true;
    pathSquares[0].wasChecked = false;
    pathSquares[1].isValid = true;
    pathSquares[1].wasChecked = false;

    TEST_ASSERT_EQUAL_INT( false, isRoadCompleteHorizontal( pathSquares, FILE_A, RANK_1, 3 ) );

    resetPathSquares(
        pathSquares,
        9
    );

    pathSquares[0].isValid = true;
    pathSquares[0].wasChecked = false;
    pathSquares[1].isValid = true;
    pathSquares[1].wasChecked = false;
    pathSquares[2].isValid = true;
    pathSquares[2].wasChecked = false;
    TEST_ASSERT_EQUAL_INT( true, isRoadCompleteHorizontal( pathSquares, FILE_A, RANK_1, 3 ) );

    TEST_ASSERT_EQUAL_INT( true, pathSquares[0].wasChecked );
    TEST_ASSERT_EQUAL_INT( true, pathSquares[1].wasChecked );
    TEST_ASSERT_EQUAL_INT( false, pathSquares[2].wasChecked );

    TEST_ASSERT_EQUAL_INT( false, pathSquares[3].wasChecked );
    TEST_ASSERT_EQUAL_INT( false, pathSquares[4].wasChecked );
    TEST_ASSERT_EQUAL_INT( false, pathSquares[5].wasChecked );

    TEST_ASSERT_EQUAL_INT( false, pathSquares[6].wasChecked );
    TEST_ASSERT_EQUAL_INT( false, pathSquares[7].wasChecked );
    TEST_ASSERT_EQUAL_INT( false, pathSquares[8].wasChecked );
}

void testCheckRoadCondition( void )
{
    Game game = newGame( 3 );
    PathSquare pathSquares[SQUARES_MAX];
    resetPathSquares(
        pathSquares,
        game.board.squareCount
    );

    game.board.stackTypes[0] = STONE_TYPE_CAP;
    game.board.stackIds[0] = PLAYER_WHITE;
    game.board.stackTypes[1] = STONE_TYPE_FLAT;
    game.board.stackIds[1] = PLAYER_WHITE;

    TEST_ASSERT_EQUAL_INT( false, isRoadComplete( &game.board, PLAYER_WHITE ) );

    resetPathSquares(
        pathSquares,
        game.board.squareCount

    );
    game.board.stackTypes[0] = STONE_TYPE_CAP;
    game.board.stackIds[0] = PLAYER_WHITE;
    game.board.stackTypes[1] = STONE_TYPE_FLAT;
    game.board.stackIds[1] = PLAYER_WHITE;
    game.board.stackTypes[2] = STONE_TYPE_FLAT;
    game.board.stackIds[2] = PLAYER_WHITE;

    TEST_ASSERT_EQUAL_INT( true, isRoadComplete( &game.board, PLAYER_WHITE ) );
}

void testIsWinConditionMet( void )
{
    Game game = newGame( 3 );

    game.board.stackTypes[0] = STONE_TYPE_CAP;
    game.board.stackIds[0] = PLAYER_WHITE;
    game.board.stackTypes[1] = STONE_TYPE_FLAT;
    game.board.stackIds[1] = PLAYER_WHITE;
    TEST_ASSERT_EQUAL_INT( false, isWinConditionMet( &game, PLAYER_WHITE ) );

    game.board.stackTypes[2] = STONE_TYPE_FLAT;
    game.board.stackIds[2] = PLAYER_WHITE;
    TEST_ASSERT_EQUAL_INT( true, isWinConditionMet( &game, PLAYER_WHITE ) );

    game.board.stackTypes[3] = STONE_TYPE_CAP;
    game.board.stackIds[3] = PLAYER_BLACK;
    game.board.stackTypes[4] = STONE_TYPE_FLAT;
    game.board.stackIds[4] = PLAYER_BLACK;
    game.board.stackTypes[7] = STONE_TYPE_FLAT;
    game.board.stackIds[7] = PLAYER_BLACK;
    TEST_ASSERT_EQUAL_INT( false, isWinConditionMet( &game, PLAYER_BLACK ) );

    game.board.stackTypes[8] = STONE_TYPE_FLAT;
    game.board.stackIds[8] = PLAYER_BLACK;
    TEST_ASSERT_EQUAL_INT( true, isWinConditionMet( &game, PLAYER_BLACK ) );

    game = newGame( 3 );
    TEST_ASSERT_EQUAL_INT( false, isWinConditionMet( &game, PLAYER_WHITE ) );
    TEST_ASSERT_EQUAL_INT( false, isWinConditionMet( &game, PLAYER_BLACK ) );

    game.reserves.regular[PLAYER_BLACK] = 0;
    TEST_ASSERT_EQUAL_INT( false, isWinConditionMet( &game, PLAYER_WHITE ) );
    TEST_ASSERT_EQUAL_INT( true, isWinConditionMet( &game, PLAYER_BLACK ) );
}

#endif
