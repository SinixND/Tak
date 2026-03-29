#ifndef IG20260327200417
#define IG20260327200417

#include "Board.h"
#include "FileId.h"
#include "GameEvent.h"
#include "GameEventSystem.h"
#include "GameSystem.h"
#include "PlayerId.h"
#include "Players.h"
#include "PositionSystem.h"
#include "RankId.h"
#include "StoneTypeId.h"
#include <stdbool.h>
#include <unity.h>

void testNewGameEvent( void )
{
    GameEvent event = newGameEvent();

    TEST_ASSERT_EQUAL_INT( PLAYER_NONE, event.stoneId );
    TEST_ASSERT_EQUAL_INT( ACTION_TYPE_NONE, event.actionType );
    TEST_ASSERT_EQUAL_INT( STONE_TYPE_NONE, event.stoneType );
    TEST_ASSERT_EQUAL_INT( FILE_NONE, event.fileX );
    TEST_ASSERT_EQUAL_INT( RANK_NONE, event.rankY );
    TEST_ASSERT_EQUAL_INT( DIR_NONE, event.direction );
    TEST_ASSERT_EQUAL_INT( 0, event.liftCount );
    TEST_ASSERT_EQUAL_INT( -1, event.dropCounts[0] );
    TEST_ASSERT_EQUAL_INT( -1, event.dropCounts[BOARD_WIDTH_MAX - 1] );
    TEST_ASSERT_EQUAL_INT( 0, event.dropCountsSize );
    TEST_ASSERT_EQUAL_INT( 0, event.droppedCount );
}

void testIsStoneTypeAvailable( void )
{
    GameEvent event;
    Players players = { 0 };

    event.stoneId = PLAYER_WHITE;

    event.stoneType = STONE_TYPE_FLAT;
    TEST_ASSERT_EQUAL_INT( false, isStoneTypeAvailable( &event, &players ) );

    event.stoneType = STONE_TYPE_STANDING;
    TEST_ASSERT_EQUAL_INT( false, isStoneTypeAvailable( &event, &players ) );

    event.stoneType = STONE_TYPE_CAP;
    TEST_ASSERT_EQUAL_INT( false, isStoneTypeAvailable( &event, &players ) );

    players.reservesRegular[event.stoneId] = 1;
    players.reservesCapstone[event.stoneId] = 1;

    event.stoneType = STONE_TYPE_FLAT;
    TEST_ASSERT_EQUAL_INT( true, isStoneTypeAvailable( &event, &players ) );

    event.stoneType = STONE_TYPE_STANDING;
    TEST_ASSERT_EQUAL_INT( true, isStoneTypeAvailable( &event, &players ) );

    event.stoneType = STONE_TYPE_CAP;
    TEST_ASSERT_EQUAL_INT( true, isStoneTypeAvailable( &event, &players ) );

    event.stoneId = PLAYER_BLACK;

    event.stoneType = STONE_TYPE_FLAT;
    TEST_ASSERT_EQUAL_INT( false, isStoneTypeAvailable( &event, &players ) );

    event.stoneType = STONE_TYPE_STANDING;
    TEST_ASSERT_EQUAL_INT( false, isStoneTypeAvailable( &event, &players ) );

    event.stoneType = STONE_TYPE_CAP;
    TEST_ASSERT_EQUAL_INT( false, isStoneTypeAvailable( &event, &players ) );

    players.reservesRegular[event.stoneId] = 1;
    players.reservesCapstone[event.stoneId] = 1;

    event.stoneType = STONE_TYPE_FLAT;
    TEST_ASSERT_EQUAL_INT( true, isStoneTypeAvailable( &event, &players ) );

    event.stoneType = STONE_TYPE_STANDING;
    TEST_ASSERT_EQUAL_INT( true, isStoneTypeAvailable( &event, &players ) );

    event.stoneType = STONE_TYPE_CAP;
    TEST_ASSERT_EQUAL_INT( true, isStoneTypeAvailable( &event, &players ) );
}

void testIsFileXOnBoard( void )
{
    GameEvent event;
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
    GameEvent event;
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
    GameEvent event;
    Board board;

    board.width = 3;
    event.fileX = FILE_B;
    event.rankY = RANK_2;
    int squareIdx = positionToSquare( event.fileX, event.rankY, board.width );

    TEST_ASSERT_EQUAL_INT( true, isSquareEmpty( &event, &board ) );

    board.stoneCounts[squareIdx] = 1;

    TEST_ASSERT_EQUAL_INT( false, isSquareEmpty( &event, &board ) );
}

void testDoesPlayerOwnStack( void )
{
    GameEvent event;
    Board board;
    board.width = 3;
    event.stoneId = PLAYER_WHITE;
    event.fileX = FILE_B;
    event.rankY = RANK_2;
    int squareIdx = positionToSquare( event.fileX, event.rankY, board.width );
    board.stoneCounts[squareIdx] = 1;
    board.stoneIds[squareIdx + board.stoneCounts[squareIdx] - 1] = PLAYER_WHITE;

    TEST_ASSERT_EQUAL_INT( true, doesPlayerOwnStack( &event, &board ) );

    event.stoneId = PLAYER_BLACK;
    TEST_ASSERT_EQUAL_INT( false, doesPlayerOwnStack( &event, &board ) );
}

void testIsCaptiveValid( void )
{
    GameEvent event;
    Board board;

    event.fileX = FILE_B;
    event.rankY = RANK_2;
    board.width = 3;

    int const squareIdx = positionToSquare(
        event.fileX,
        event.rankY,
        board.width
    );

    board.types[squareIdx] = STONE_TYPE_FLAT;
    event.stoneType = STONE_TYPE_FLAT;
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

// void testIsOffsetXOnBoard( void )
// {
//     GameEvent event ;
// }

// void testIsOffsetYOnBoard( void )
// {
//     GameEvent event ;
// }

// void testValidateEventPlace( void )
// {
//     GameEvent event ;
//     Game game ;
// }

// void testValidateEventLift( void )
// {
//     GameEvent event ;
//     Game game ;
// }

// void testValidateEventDrop( void )
// {
//     GameEvent event ;
//     Game game ;
// }

#endif
