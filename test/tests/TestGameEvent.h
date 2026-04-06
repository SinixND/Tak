#ifndef IG20260406173020
#define IG20260406173020

#include "ActionTypeId.h"
#include "Board.h"
#include "FileId.h"
#include "GameEvent.h"
#include "GameEventValidation.h"
#include "PlayerId.h"
#include "PositionSystem.h"
#include "RankId.h"
#include "Reserves.h"
#include "StoneTypeId.h"
#include <stdbool.h>
#include <unity.h>

void testNewGameEvent( void )
{
    GameEvent event = newGameEvent();

    TEST_ASSERT_EQUAL_INT( PLAYER_NONE, event.playerId );
    TEST_ASSERT_EQUAL_INT( ACTION_TYPE_NONE, event.actionType );
    TEST_ASSERT_EQUAL_INT( STONE_TYPE_NONE, event.stoneType );
    TEST_ASSERT_EQUAL_INT( FILE_NONE, event.fileX );
    TEST_ASSERT_EQUAL_INT( RANK_NONE, event.rankY );
    TEST_ASSERT_EQUAL_INT( 0, event.dropCount );
}

void testIsStoneTypeAvailable( void )
{
    GameEvent event = { 0 };
    Reserves reserves = { 0 };

    event.playerId = PLAYER_WHITE;
    event.stoneType = STONE_TYPE_FLAT;
    TEST_ASSERT_EQUAL_INT( false, isStoneTypeAvailable( &event, &reserves ) );

    event.stoneType = STONE_TYPE_STANDING;
    TEST_ASSERT_EQUAL_INT( false, isStoneTypeAvailable( &event, &reserves ) );

    event.stoneType = STONE_TYPE_CAP;
    TEST_ASSERT_EQUAL_INT( false, isStoneTypeAvailable( &event, &reserves ) );

    reserves.regular[event.playerId] = 1;
    reserves.capstone[event.playerId] = 1;

    event.stoneType = STONE_TYPE_FLAT;
    TEST_ASSERT_EQUAL_INT( true, isStoneTypeAvailable( &event, &reserves ) );

    event.stoneType = STONE_TYPE_STANDING;
    TEST_ASSERT_EQUAL_INT( true, isStoneTypeAvailable( &event, &reserves ) );

    event.stoneType = STONE_TYPE_CAP;
    TEST_ASSERT_EQUAL_INT( true, isStoneTypeAvailable( &event, &reserves ) );

    event.playerId = PLAYER_BLACK;

    event.stoneType = STONE_TYPE_FLAT;
    TEST_ASSERT_EQUAL_INT( false, isStoneTypeAvailable( &event, &reserves ) );

    event.stoneType = STONE_TYPE_STANDING;
    TEST_ASSERT_EQUAL_INT( false, isStoneTypeAvailable( &event, &reserves ) );

    event.stoneType = STONE_TYPE_CAP;
    TEST_ASSERT_EQUAL_INT( false, isStoneTypeAvailable( &event, &reserves ) );

    reserves.regular[event.playerId] = 1;
    reserves.capstone[event.playerId] = 1;

    event.stoneType = STONE_TYPE_FLAT;
    TEST_ASSERT_EQUAL_INT( true, isStoneTypeAvailable( &event, &reserves ) );

    event.stoneType = STONE_TYPE_STANDING;
    TEST_ASSERT_EQUAL_INT( true, isStoneTypeAvailable( &event, &reserves ) );

    event.stoneType = STONE_TYPE_CAP;
    TEST_ASSERT_EQUAL_INT( true, isStoneTypeAvailable( &event, &reserves ) );
}

void testIsFileXOnBoard( void )
{
    GameEvent event = { 0 };
    int boardWidth = 3;

    event.fileX = FILE_NONE;
    TEST_ASSERT_EQUAL_INT( false, isFileXOnBoard( &event, boardWidth ) );

    event.fileX = FILE_A;
    TEST_ASSERT_EQUAL_INT( true, isFileXOnBoard( &event, boardWidth ) );

    event.fileX = FILE_C;
    TEST_ASSERT_EQUAL_INT( true, isFileXOnBoard( &event, boardWidth ) );

    event.fileX = FILE_D;
    TEST_ASSERT_EQUAL_INT( false, isFileXOnBoard( &event, boardWidth ) );

    boardWidth = 7;

    event.fileX = FILE_NONE;
    TEST_ASSERT_EQUAL_INT( false, isFileXOnBoard( &event, boardWidth ) );

    event.fileX = FILE_A;
    TEST_ASSERT_EQUAL_INT( true, isFileXOnBoard( &event, boardWidth ) );

    event.fileX = FILE_G;
    TEST_ASSERT_EQUAL_INT( true, isFileXOnBoard( &event, boardWidth ) );

    event.fileX = FILE_H;
    TEST_ASSERT_EQUAL_INT( false, isFileXOnBoard( &event, boardWidth ) );

    boardWidth = 8;

    event.fileX = FILE_NONE;
    TEST_ASSERT_EQUAL_INT( false, isFileXOnBoard( &event, boardWidth ) );

    event.fileX = FILE_A;
    TEST_ASSERT_EQUAL_INT( true, isFileXOnBoard( &event, boardWidth ) );

    event.fileX = FILE_H;
    TEST_ASSERT_EQUAL_INT( true, isFileXOnBoard( &event, boardWidth ) );
}

void testIsRankYOnBoard( void )
{
    GameEvent event = { 0 };
    int boardWidth = 3;

    event.rankY = RANK_NONE;
    TEST_ASSERT_EQUAL_INT( false, isRankYOnBoard( &event, boardWidth ) );

    event.rankY = RANK_1;
    TEST_ASSERT_EQUAL_INT( true, isRankYOnBoard( &event, boardWidth ) );

    event.rankY = RANK_3;
    TEST_ASSERT_EQUAL_INT( true, isRankYOnBoard( &event, boardWidth ) );

    event.rankY = RANK_4;
    TEST_ASSERT_EQUAL_INT( false, isRankYOnBoard( &event, boardWidth ) );

    boardWidth = 7;

    event.rankY = RANK_NONE;
    TEST_ASSERT_EQUAL_INT( false, isRankYOnBoard( &event, boardWidth ) );

    event.rankY = RANK_1;
    TEST_ASSERT_EQUAL_INT( true, isRankYOnBoard( &event, boardWidth ) );

    event.rankY = RANK_7;
    TEST_ASSERT_EQUAL_INT( true, isRankYOnBoard( &event, boardWidth ) );

    event.rankY = RANK_8;
    TEST_ASSERT_EQUAL_INT( false, isRankYOnBoard( &event, boardWidth ) );

    boardWidth = 8;

    event.rankY = RANK_NONE;
    TEST_ASSERT_EQUAL_INT( false, isRankYOnBoard( &event, boardWidth ) );

    event.rankY = RANK_1;
    TEST_ASSERT_EQUAL_INT( true, isRankYOnBoard( &event, boardWidth ) );

    event.rankY = RANK_8;
    TEST_ASSERT_EQUAL_INT( true, isRankYOnBoard( &event, boardWidth ) );
}

void testIsSquareEmpty( void )
{
    GameEvent event = { 0 };
    Board board;

    board.width = 3;
    event.fileX = FILE_B;
    event.rankY = RANK_2;
    int squareIdx = positionToSquare(
        event.fileX,
        event.rankY,
        board.width
    );

    TEST_ASSERT_EQUAL_INT( true, isSquareEmpty( &event, &board ) );

    board.stoneCounts[squareIdx] = 1;

    TEST_ASSERT_EQUAL_INT( false, isSquareEmpty( &event, &board ) );
}

void testDoesPlayerOwnStack( void )
{
    GameEvent event = { 0 };
    Board board;
    board.width = 3;
    event.playerId = PLAYER_WHITE;
    event.fileX = FILE_B;
    event.rankY = RANK_2;
    int squareIdx = positionToSquare(
        event.fileX,
        event.rankY,
        board.width
    );
    board.stoneCounts[squareIdx] = 1;
    board.stoneIds[squareToStackIndex( squareIdx, board.stackCapacity ) + board.stoneCounts[squareIdx] - 1] = PLAYER_WHITE;
    TEST_ASSERT_EQUAL_INT( true, doesPlayerOwnStack( &event, &board ) );

    event.playerId = PLAYER_BLACK;
    TEST_ASSERT_EQUAL_INT( false, doesPlayerOwnStack( &event, &board ) );
}

void testIsCaptiveValid( void )
{
    GameEvent event = { 0 };
    Board board = { 0 };

    event.fileX = FILE_B;
    event.rankY = RANK_2;
    event.stoneType = STONE_TYPE_FLAT;

    board.width = 3;

    int const squareIdx = positionToSquare(
        event.fileX,
        event.rankY,
        board.width
    );

    board.types[squareIdx] = STONE_TYPE_FLAT;
    TEST_ASSERT_EQUAL_INT( true, isCaptiveValid( &event, &board ) );

    event.stoneType = STONE_TYPE_STANDING;
    TEST_ASSERT_EQUAL_INT( true, isCaptiveValid( &event, &board ) );

    event.stoneType = STONE_TYPE_CAP;
    TEST_ASSERT_EQUAL_INT( true, isCaptiveValid( &event, &board ) );

    board.types[squareIdx] = STONE_TYPE_STANDING;
    event.stoneType = STONE_TYPE_FLAT;
    TEST_ASSERT_EQUAL_INT( false, isCaptiveValid( &event, &board ) );

    event.stoneType = STONE_TYPE_STANDING;
    TEST_ASSERT_EQUAL_INT( false, isCaptiveValid( &event, &board ) );

    event.stoneType = STONE_TYPE_CAP;
    TEST_ASSERT_EQUAL_INT( true, isCaptiveValid( &event, &board ) );

    board.types[squareIdx] = STONE_TYPE_CAP;
    event.stoneType = STONE_TYPE_FLAT;
    TEST_ASSERT_EQUAL_INT( false, isCaptiveValid( &event, &board ) );

    event.stoneType = STONE_TYPE_STANDING;
    TEST_ASSERT_EQUAL_INT( false, isCaptiveValid( &event, &board ) );

    event.stoneType = STONE_TYPE_CAP;
    TEST_ASSERT_EQUAL_INT( false, isCaptiveValid( &event, &board ) );
}

void testIsDropCountValid( void )
{
    GameEvent event = { 0 };
    int stackBufferStoneCount = 0;

    event.dropCount = 1;

    TEST_ASSERT_EQUAL_INT( false, isDropCountValid( &event, stackBufferStoneCount ) );

    stackBufferStoneCount = 1;
    TEST_ASSERT_EQUAL_INT( true, isDropCountValid( &event, stackBufferStoneCount ) );
}

#endif
