#ifndef IG20260327200417
#define IG20260327200417

#include "FileId.h"
#include "GameEvent.h"
#include "GameEventSystem.h"
#include "GameSystem.h"
#include "PlayerId.h"
#include "Players.h"
#include "RankId.h"
#include "StoneTypeId.h"
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

// void testIsSquareEmpty( void )
// {
//     GameEvent event = newGameEvent();
// }

// void testDoesPlayerOwnStack( void )
// {
//     GameEvent event = newGameEvent();
// }

// void testIsCaptiveValid( void )
// {
//     GameEvent event = newGameEvent();
// }

// void testIsOffsetXOnBoard( void )
// {
//     GameEvent event = newGameEvent();
// }

// void testIsOffsetYOnBoard( void )
// {
//     GameEvent event = newGameEvent();
// }

// void testValidateEventPlace( void )
// {
//     GameEvent event = newGameEvent();
//     Game game = newGame( 0 );
// }

// void testValidateEventLift( void )
// {
//     GameEvent event = newGameEvent();
//     Game game = newGame( 0 );
// }

// void testValidateEventDrop( void )
// {
//     GameEvent event = newGameEvent();
//     Game game = newGame( 0 );
// }

#endif
