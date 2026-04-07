#ifndef IG20260406172817
#define IG20260406172817

#include "Event.h"
#include "Game.h"
#include "PositionSystem.h"
#include "RuleValidation.h"
#include <unity.h>

void testIsStoneTypeAvailable( void )
{
    Event event = { 0 };
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
    Event event = { 0 };
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
    Event event = { 0 };
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
    Event event = { 0 };
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
    Event event = { 0 };
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
    Event event = { 0 };
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

    board.stackTypes[squareIdx] = STONE_TYPE_FLAT;
    TEST_ASSERT_EQUAL_INT( true, isCaptiveValid( &event, &board ) );

    event.stoneType = STONE_TYPE_STANDING;
    TEST_ASSERT_EQUAL_INT( true, isCaptiveValid( &event, &board ) );

    event.stoneType = STONE_TYPE_CAP;
    TEST_ASSERT_EQUAL_INT( true, isCaptiveValid( &event, &board ) );

    board.stackTypes[squareIdx] = STONE_TYPE_STANDING;
    event.stoneType = STONE_TYPE_FLAT;
    TEST_ASSERT_EQUAL_INT( false, isCaptiveValid( &event, &board ) );

    event.stoneType = STONE_TYPE_STANDING;
    TEST_ASSERT_EQUAL_INT( false, isCaptiveValid( &event, &board ) );

    event.stoneType = STONE_TYPE_CAP;
    TEST_ASSERT_EQUAL_INT( true, isCaptiveValid( &event, &board ) );

    board.stackTypes[squareIdx] = STONE_TYPE_CAP;
    event.stoneType = STONE_TYPE_FLAT;
    TEST_ASSERT_EQUAL_INT( false, isCaptiveValid( &event, &board ) );

    event.stoneType = STONE_TYPE_STANDING;
    TEST_ASSERT_EQUAL_INT( false, isCaptiveValid( &event, &board ) );

    event.stoneType = STONE_TYPE_CAP;
    TEST_ASSERT_EQUAL_INT( false, isCaptiveValid( &event, &board ) );
}

void testIsDropCountValid( void )
{
    Event event = { 0 };
    int stackBufferStoneCount = 0;

    event.dropCount = 1;

    TEST_ASSERT_EQUAL_INT( false, isDropCountValid( &event, stackBufferStoneCount ) );

    stackBufferStoneCount = 1;
    TEST_ASSERT_EQUAL_INT( true, isDropCountValid( &event, stackBufferStoneCount ) );
}

void testValidateEventPlace( void )
{
    Event event = { 0 };
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
    Event event = { 0 };
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
    Event event = { 0 };
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

    game.board.stackTypes[squareIdx] = STONE_TYPE_STANDING;
    TEST_ASSERT_EQUAL_INT( false, validateEventDrop( &event, &game ) );

    game.board.stackTypes[squareIdx] = STONE_TYPE_FLAT;
    TEST_ASSERT_EQUAL_INT( true, validateEventDrop( &event, &game ) );
}

#endif
