#ifndef IG20260406172817
#define IG20260406172817

#include "Game.h"
#include "GameEvent.h"
#include "GameEventValidation.h"
#include "PositionSystem.h"
#include <unity.h>

void testValidateEventPlace( void )
{
    GameEvent event = { 0 };
    Game game = { 0 };

    event.stoneType = STONE_TYPE_FLAT;
    event.playerId = PLAYER_WHITE;
    event.fileX = FILE_B;
    event.rankY = RANK_2;

    game.reserves.regular[event.playerId] = 1;
    game.board.width = 3;

    TEST_ASSERT_EQUAL_INT( true, validateEventPlace( &event, &game ) );

    int const squareIdx = positionToSquare(
        event.fileX,
        event.rankY,
        game.board.width
    );

    game.board.stoneCounts[squareIdx] = 1;

    TEST_ASSERT_EQUAL_INT( false, validateEventPlace( &event, &game ) );

    event.fileX = FILE_D;

    TEST_ASSERT_EQUAL_INT( false, validateEventPlace( &event, &game ) );

    event.fileX = FILE_C;
    event.rankY = RANK_4;

    TEST_ASSERT_EQUAL_INT( false, validateEventPlace( &event, &game ) );

    event.rankY = RANK_3;
    game.reserves.regular[event.playerId] = 0;

    TEST_ASSERT_EQUAL_INT( false, validateEventPlace( &event, &game ) );
}

void testValidateEventLift( void )
{
    GameEvent event = { 0 };
    Game game = { 0 };

    event.fileX = FILE_B;
    event.rankY = RANK_2;

    game.board.width = 3;

    int const squareIdx = positionToSquare(
        event.fileX,
        event.rankY,
        game.board.width
    );

    game.board.stoneCounts[squareIdx] = 1;
    game.board.stoneIds[squareToStackIndex( squareIdx, game.board.stackCapacity ) + game.board.stoneCounts[squareIdx] - 1] = PLAYER_WHITE;

    TEST_ASSERT_EQUAL_INT( true, validateEventLift( &event, &game ) );

    event.fileX = FILE_D;

    TEST_ASSERT_EQUAL_INT( false, validateEventLift( &event, &game ) );

    event.fileX = FILE_C;
    event.rankY = RANK_4;

    TEST_ASSERT_EQUAL_INT( false, validateEventLift( &event, &game ) );

    event.rankY = RANK_3;
    game.board.stoneCounts[squareIdx] = 0;

    TEST_ASSERT_EQUAL_INT( false, validateEventLift( &event, &game ) );

    game.board.stoneCounts[squareIdx] = 1;
    game.board.stoneIds[squareToStackIndex( squareIdx, game.board.stackCapacity ) + game.board.stoneCounts[squareIdx] - 1] = PLAYER_BLACK;

    TEST_ASSERT_EQUAL_INT( false, validateEventLift( &event, &game ) );
}

void testValidateEventDrop( void )
{
    GameEvent event = { 0 };
    Game game = { 0 };

    event.dropCount = 1;
    game.board.width = 3;

    game.stackBuffer.stoneCount = 0;
    TEST_ASSERT_EQUAL_INT( false, validateEventDrop( &event, &game ) );

    game.stackBuffer.stoneCount = 1;
    TEST_ASSERT_EQUAL_INT( true, validateEventDrop( &event, &game ) );

    event.fileX = FILE_B;
    event.rankY = RANK_2;

    event.stoneType = STONE_TYPE_FLAT;

    int const squareIdx = positionToSquare(
        event.fileX,
        event.rankY,
        game.board.width
    );

    game.board.types[squareIdx] = STONE_TYPE_STANDING;
    TEST_ASSERT_EQUAL_INT( false, validateEventDrop( &event, &game ) );

    game.board.types[squareIdx] = STONE_TYPE_FLAT;
    TEST_ASSERT_EQUAL_INT( true, validateEventDrop( &event, &game ) );
}

void testValidateEvent( void )
{
    GameEvent event = { 0 };
    Game game = { 0 };

    event.stoneType = STONE_TYPE_FLAT;
    event.playerId = PLAYER_WHITE;
    event.fileX = FILE_B;
    event.rankY = RANK_2;

    game.board.width = 3;
    game.reserves.regular[event.playerId] = 1;
    game.stackBuffer.stoneCount = 1;

    int const squareIdx = positionToSquare(
        event.fileX,
        event.rankY,
        game.board.width
    );

    event.actionType = ACTION_TYPE_PLACE;

    game.reserves.regular[event.playerId] = 0;
    TEST_ASSERT_EQUAL_INT( false, validateEvent( &event, &game ) );

    game.reserves.regular[event.playerId] = 1;
    TEST_ASSERT_EQUAL_INT( true, validateEvent( &event, &game ) );

    event.actionType = ACTION_TYPE_LIFT;

    game.board.stoneCounts[squareIdx] = 0;
    TEST_ASSERT_EQUAL_INT( false, validateEvent( &event, &game ) );

    game.board.stoneCounts[squareIdx] = 1;
    TEST_ASSERT_EQUAL_INT( true, validateEvent( &event, &game ) );

    event.actionType = ACTION_TYPE_DROP;

    event.dropCount = 1;

    game.stackBuffer.stoneCount = 0;
    TEST_ASSERT_EQUAL_INT( false, validateEvent( &event, &game ) );

    game.stackBuffer.stoneCount = 1;
    TEST_ASSERT_EQUAL_INT( true, validateEvent( &event, &game ) );
}

#endif
