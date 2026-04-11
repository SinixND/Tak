#ifndef IG20260410171141
#define IG20260410171141

#include "Engine.h"
#include "Game.h"
#include "GameConstants.h"
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

void testExecuteEvent( void )
{
    Event event = newEvent();
    Game game = newGame( 5 );

    event.actionType = ACTION_TYPE_PLACE;
    event.playerId = PLAYER_WHITE;
    event.squareIdx = 0;
    event.stoneType = STONE_TYPE_STANDING;

    executeEvent( &game, &event );

    TEST_ASSERT_EQUAL_INT( getReservesRegular( 5 ) - 1, game.reserves.regular[PLAYER_WHITE] );
    TEST_ASSERT_EQUAL_INT( getReservesCapstone( 5 ), game.board.stoneCounts[0] );
    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, game.board.stoneIds[0] );
    TEST_ASSERT_EQUAL_INT( PLAYER_NONE, game.board.stoneIds[1] );
    TEST_ASSERT_EQUAL_INT( STONE_TYPE_STANDING, game.board.stackTypes[0] );

    event.actionType = ACTION_TYPE_LIFT;

    executeEvent( &game, &event );

    TEST_ASSERT_EQUAL_INT( STONE_TYPE_STANDING, game.stackBuffer.stoneType );
    TEST_ASSERT_EQUAL_INT( 1, game.stackBuffer.stoneCount );
    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, game.stackBuffer.stoneIds[0] );

    TEST_ASSERT_EQUAL_INT( 0, game.board.stoneCounts[0] );

    event.actionType = ACTION_TYPE_DROP;
    event.dropCount = 1;

    executeEvent( &game, &event );

    TEST_ASSERT_EQUAL_INT( STONE_TYPE_STANDING, game.board.stackTypes[0] );
    TEST_ASSERT_EQUAL_INT( 1, game.board.stoneCounts[0] );
    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, game.board.stoneIds[0] );
}
#endif
