#ifndef IG20260406172737
#define IG20260406172737

#include "Game.h"
#include "GameEvent.h"
#include "GameEventExecution.h"
#include <unity.h>

void testApplyEvent( void )
{
    Game game = newGame( 5 );
    GameEvent event = { 0 };

    event.playerId = PLAYER_WHITE;
    event.actionType = ACTION_TYPE_PLACE;
    event.fileX = FILE_A;
    event.rankY = RANK_1;
    event.stoneType = STONE_TYPE_FLAT;

    applyEvent(
        &game,
        &event
    );

    TEST_ASSERT_EQUAL_INT( 20, game.reserves.regular[PLAYER_WHITE] );
    TEST_ASSERT_EQUAL_INT( 1, game.board.stoneCounts[0] );
    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, game.board.stoneIds[0] );
    TEST_ASSERT_EQUAL_INT( PLAYER_NONE, game.board.stoneIds[1] );
    TEST_ASSERT_EQUAL_INT( STONE_TYPE_FLAT, game.board.types[0] );

    event.actionType = ACTION_TYPE_LIFT;

    applyEvent(
        &game,
        &event
    );

    TEST_ASSERT_EQUAL_INT( 0, game.board.stoneCounts[0] );
    TEST_ASSERT_EQUAL_INT( 1, game.stackBuffer.stoneCount );

    event.actionType = ACTION_TYPE_DROP;
    event.dropCount = 1;

    applyEvent(
        &game,
        &event
    );

    TEST_ASSERT_EQUAL_INT( 1, game.board.stoneCounts[0] );
}

#endif
