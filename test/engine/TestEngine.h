#ifndef IG20260410171141
#define IG20260410171141

#include "Command.h"
#include "Engine.h"
#include "Game.h"
#include "GameConstants.h"
#include "PlayerId.h"
#include "RankId.h"
#include "StoneTypeId.h"
#include <unity.h>

void testNewEngine( void )
{
    Engine engine = newEngine();

    TEST_ASSERT_EQUAL_INT( PLAYER_NONE, engine.event.playerId );
    TEST_ASSERT_EQUAL_INT( ACTION_TYPE_NONE, engine.event.actionType );
    TEST_ASSERT_EQUAL_INT( STONE_TYPE_NONE, engine.event.stoneType );
    TEST_ASSERT_EQUAL_INT( -1, engine.event.squareIdx );
    TEST_ASSERT_EQUAL_INT( -1, engine.event.dropCount );

    TEST_ASSERT_EQUAL_INT( PLAYER_NONE, engine.command.playerId );
    TEST_ASSERT_EQUAL_INT( ACTION_TYPE_NONE, engine.command.actionType );
    TEST_ASSERT_EQUAL_INT( STONE_TYPE_NONE, engine.command.stoneType );
    TEST_ASSERT_EQUAL_INT( FILE_NONE, engine.command.fileX );
    TEST_ASSERT_EQUAL_INT( RANK_NONE, engine.command.rankY );
    TEST_ASSERT_EQUAL_INT( DIR_NONE, engine.command.direction );
    TEST_ASSERT_EQUAL_INT( -1, engine.command.drops );
    TEST_ASSERT_EQUAL_INT( -1, engine.command.dropCounts[0] );
    TEST_ASSERT_EQUAL_INT( -1, engine.command.dropCounts[7] );
}

void testBuildEvent( void )
{
    Event event = newEvent();
    Command command = newCommand();
    int const boardSize = 5;

    command.playerId = PLAYER_WHITE;
    command.actionType = ACTION_TYPE_PLACE;
    command.stoneType = STONE_TYPE_STANDING;
    command.fileX = FILE_B;
    command.rankY = RANK_2;
    command.direction = DIR_DOWN;
    command.dropCounts[0] = 0;
    command.dropCounts[1] = 2;
    command.drops = 2;

    buildEvent(
        &event,
        &command,
        boardSize
    );

    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, event.playerId );
    TEST_ASSERT_EQUAL_INT( ACTION_TYPE_PLACE, event.actionType );
    TEST_ASSERT_EQUAL_INT( STONE_TYPE_STANDING, event.stoneType );
    TEST_ASSERT_EQUAL_INT( 6, event.squareIdx );
    TEST_ASSERT_EQUAL_INT( 2, event.dropCount );
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

    TEST_ASSERT_EQUAL_INT( STONE_TYPE_STANDING, game.stackBuffer.stoneType );
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

#endif
