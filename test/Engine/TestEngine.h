#ifndef IG20260415174842
#define IG20260415174842

#include "ActionTypeId.h"
#include "App.h"
#include "Command.h"
#include "CommandStateId.h"
#include "DirectionId.h"
#include "Engine.h"
#include "Event.h"
#include "FileId.h"
#include "Game.h"
#include "History.h"
#include "InputBuffer.h"
#include "InputId.h"
#include "PlayerId.h"
#include "RankId.h"
#include "StoneTypeId.h"
#include <unity.h>

void testSetBoardSize( void )
{
    App app = newApp();

    app.inputBuffer.lastInput = INPUT_2;
    TEST_ASSERT_EQUAL_INT( false, setBoardSize( &app.game, &app.inputBuffer ) );

    app.inputBuffer.lastInput = INPUT_3;
    TEST_ASSERT_EQUAL_INT( true, setBoardSize( &app.game, &app.inputBuffer ) );
    TEST_ASSERT_EQUAL_INT( 3, app.game.board.size );

    app.inputBuffer.lastInput = INPUT_4;
    TEST_ASSERT_EQUAL_INT( true, setBoardSize( &app.game, &app.inputBuffer ) );
    TEST_ASSERT_EQUAL_INT( 4, app.game.board.size );

    app.inputBuffer.lastInput = INPUT_5;
    TEST_ASSERT_EQUAL_INT( true, setBoardSize( &app.game, &app.inputBuffer ) );
    TEST_ASSERT_EQUAL_INT( 5, app.game.board.size );

    app.inputBuffer.lastInput = INPUT_SPACE;
    TEST_ASSERT_EQUAL_INT( true, setBoardSize( &app.game, &app.inputBuffer ) );
    TEST_ASSERT_EQUAL_INT( BOARD_SIZE_DEFAULT, app.game.board.size );

    app.inputBuffer.lastInput = INPUT_6;
    TEST_ASSERT_EQUAL_INT( true, setBoardSize( &app.game, &app.inputBuffer ) );
    TEST_ASSERT_EQUAL_INT( 6, app.game.board.size );

    app.inputBuffer.lastInput = INPUT_7;
    TEST_ASSERT_EQUAL_INT( true, setBoardSize( &app.game, &app.inputBuffer ) );
    TEST_ASSERT_EQUAL_INT( 7, app.game.board.size );

    app.inputBuffer.lastInput = INPUT_8;
    TEST_ASSERT_EQUAL_INT( true, setBoardSize( &app.game, &app.inputBuffer ) );
    TEST_ASSERT_EQUAL_INT( 8, app.game.board.size );
}

void testAutocompleteCommand( void )
{
    Command command = newCommand( PLAYER_WHITE );
    Game game = newGame( 3 );

    command.fileX = FILE_A;
    command.rankY = RANK_1;
    command.direction = DIR_RIGHT;

    /// Need to drop all if next square out of board
    command.state = COMMAND_STATE_GET_DROP_AMOUNT;
    command.drops = 2; // Next square index is out of board
    command.dropCounts[0] = 0;
    command.dropCounts[1] = 1;
    game.stackBuffer.stoneCount = 2; // Two stones left in stack after previous drops
    autocompleteCommand(
        &command,
        &game
    );
    TEST_ASSERT_EQUAL_INT( 2, command.dropCounts[2] );
    TEST_ASSERT_EQUAL_INT( COMMAND_STATE_DEFAULT, command.state );

    /// Drop nothing at source square if single pickup
    command.state = COMMAND_STATE_GET_FIRST_DROP_AMOUNT;
    game.stackBuffer.stoneCount = 1; // Only one stone in stack
    command.dropCounts[0] = -1;      // No drops
    command.drops = 0;               // First drop
    autocompleteCommand(
        &command,
        &game
    );
    TEST_ASSERT_EQUAL_INT( 0, command.dropCounts[0] );
    TEST_ASSERT_EQUAL_INT( COMMAND_STATE_GET_DROP_AMOUNT, command.state );

    /// Need to drop 'all' if only one stone left in stack buffer and not first drop
    command.state = COMMAND_STATE_GET_DROP_AMOUNT;
    game.stackBuffer.stoneCount = 1; // Only one stone left in stack
    command.dropCounts[1] = -1;      // No drops
    command.drops = 1;               // Not first drop
    autocompleteCommand(
        &command,
        &game
    );
    TEST_ASSERT_EQUAL_INT( 1, command.dropCounts[1] );
    TEST_ASSERT_EQUAL_INT( COMMAND_STATE_DEFAULT, command.state );

    /// Need to drop all if next squares type is capstone
    game.stackBuffer.stoneCount = 2;
    command.state = COMMAND_STATE_GET_FIRST_DROP_AMOUNT;
    command.drops = 0;                         // Next square index is 0
    game.board.stackTypes[1] = STONE_TYPE_CAP; // Next squares type is capstone
    autocompleteCommand(
        &command,
        &game
    );
    TEST_ASSERT_EQUAL_INT( 2, command.dropCounts[0] );
    TEST_ASSERT_EQUAL_INT( COMMAND_STATE_DEFAULT, command.state );

    /// Need to drop all if next squares type is standing and buffer type is not capstone
    game.stackBuffer.stoneCount = 2;
    command.state = COMMAND_STATE_GET_FIRST_DROP_AMOUNT;
    command.drops = 0;                              // Next square index is 0
    game.board.stackTypes[1] = STONE_TYPE_STANDING; // Next squares type is standing
    game.stackBuffer.stackType = STONE_TYPE_FLAT;   // Buffertype is not capstone
    autocompleteCommand(
        &command,
        &game
    );
    TEST_ASSERT_EQUAL_INT( 2, command.dropCounts[0] );
    TEST_ASSERT_EQUAL_INT( COMMAND_STATE_DEFAULT, command.state );

    /// Need to drop all but one if
    /// - next squares type is standing
    /// - buffer type is capstone
    /// - this is the first drop
    game.stackBuffer.stoneCount = 2;
    command.state = COMMAND_STATE_GET_FIRST_DROP_AMOUNT;
    command.drops = 0;                              // Next square index is 0
    game.board.stackTypes[1] = STONE_TYPE_STANDING; // Next squares type is standing
    game.stackBuffer.stackType = STONE_TYPE_CAP;    // Buffertype is capstone
    autocompleteCommand(
        &command,
        &game
    );
    TEST_ASSERT_EQUAL_INT( 1, command.dropCounts[0] );
}

void testBuildCommand( void )
{
    Command command = newCommand( PLAYER_WHITE );
    InputBuffer inputBuffer = newInputBuffer();
    Game game = newGame( 5 );

    command.fileX = FILE_A;
    command.rankY = RANK_1;
    command.state = COMMAND_STATE_GET_DROP_AMOUNT;
    command.actionType = ACTION_TYPE_DROP;
    command.drops = 1;
    command.dropCounts[0] = 2;
    game.stackBuffer.stoneCount = 3;
    inputBuffer.lastInput = INPUT_4;

    buildCommand(
        &command,
        &inputBuffer,
        &game
    );

    TEST_ASSERT_EQUAL_INT( 3, command.dropCounts[1] );
}

void testBuildEvent( void )
{
    Event event = newEvent();
    Command command = newCommand( PLAYER_WHITE );
    int const boardSize = 5;

    command.playerId = PLAYER_WHITE;
    command.actionType = ACTION_TYPE_PLACE;
    command.stoneType = STONE_TYPE_STANDING;
    command.fileX = FILE_B;
    command.rankY = RANK_2;
    command.direction = DIR_DOWN;
    command.dropCounts[0] = 0;
    command.dropCounts[1] = 2;
    command.drops = 1;

    buildEvent(
        &event,
        &command,
        boardSize
    );

    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, event.playerId );
    TEST_ASSERT_EQUAL_INT( ACTION_TYPE_PLACE, event.actionType );
    TEST_ASSERT_EQUAL_INT( STONE_TYPE_STANDING, event.stoneType );
    TEST_ASSERT_EQUAL_INT( 1, event.squareIdx );
    TEST_ASSERT_EQUAL_INT( 2, event.dropCount );
}

void testUndoTurn( void )
{
    App app = newApp();
    app.inputBuffer.lastInput = INPUT_3;
    setBoardSize( &app.game, &app.inputBuffer );

    // app.command.state = COMMAND_STATE_GET_RANK_Y;
    app.command.actionType = ACTION_TYPE_PLACE;
    app.command.stoneType = STONE_TYPE_STANDING;
    app.command.playerId = PLAYER_WHITE;
    app.command.fileX = FILE_A;
    app.command.rankY = RANK_1;
    updateGame( &app );

    // app.command.state = COMMAND_STATE_GET_RANK_Y;
    app.command.actionType = ACTION_TYPE_LIFT;
    app.command.fileX = FILE_A;
    app.command.rankY = RANK_1;
    updateGame( &app );

    // app.command.state = COMMAND_STATE_GET_FIRST_DROP_AMOUNT;
    app.command.actionType = ACTION_TYPE_DROP;
    app.command.fileX = FILE_A;
    app.command.rankY = RANK_1;
    app.command.direction = DIR_RIGHT;
    app.command.drops = 0;
    app.command.dropCounts[0] = 0;
    updateGame( &app );

    // app.command.state = COMMAND_STATE_GET_DROP_AMOUNT;
    app.command.actionType = ACTION_TYPE_DROP;
    app.command.fileX = FILE_A;
    app.command.rankY = RANK_1;
    app.command.direction = DIR_RIGHT;
    app.command.drops = 1;
    app.command.dropCounts[1] = 1;
    updateGame( &app );

    undoTurn(
        &app.history,
        &app.game
    );

    undoTurn(
        &app.history,
        &app.game
    );

    undoTurn(
        &app.history,
        &app.game
    );

    undoTurn(
        &app.history,
        &app.game
    );

    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, app.game.board.stoneIds[0] );
    TEST_ASSERT_EQUAL_INT( 1, app.game.board.stoneCounts[0] );
    TEST_ASSERT_EQUAL_INT( STONE_TYPE_STANDING, app.game.board.stackTypes[0] );
    TEST_ASSERT_EQUAL_INT( 0, app.game.board.stoneCounts[1] );

    TEST_ASSERT_EQUAL_INT( 1, app.history.lastRecordIdx );
    TEST_ASSERT_EQUAL_INT( 4, app.history.totalRecords );
}

void testRedoTurn( void )
{
    App app = newApp();
    app.inputBuffer.lastInput = INPUT_3;
    setBoardSize( &app.game, &app.inputBuffer );

    // app.command.state = COMMAND_STATE_GET_RANK_Y;
    app.command.actionType = ACTION_TYPE_PLACE;
    app.command.stoneType = STONE_TYPE_STANDING;
    app.command.playerId = PLAYER_WHITE;
    app.command.fileX = FILE_A;
    app.command.rankY = RANK_1;
    updateGame( &app );

    // app.command.state = COMMAND_STATE_GET_RANK_Y;
    app.command.actionType = ACTION_TYPE_LIFT;
    app.command.fileX = FILE_A;
    app.command.rankY = RANK_1;
    updateGame( &app );

    // app.command.state = COMMAND_STATE_GET_FIRST_DROP_AMOUNT;
    app.command.actionType = ACTION_TYPE_DROP;
    app.command.fileX = FILE_A;
    app.command.rankY = RANK_1;
    app.command.direction = DIR_RIGHT;
    app.command.drops = 0;
    app.command.dropCounts[0] = 0;
    updateGame( &app );

    // app.command.state = COMMAND_STATE_GET_DROP_AMOUNT;
    app.command.actionType = ACTION_TYPE_DROP;
    app.command.fileX = FILE_A;
    app.command.rankY = RANK_1;
    app.command.direction = DIR_RIGHT;
    app.command.drops = 1;
    app.command.dropCounts[1] = 1;
    updateGame( &app );

    undoTurn(
        &app.history,
        &app.game
    );

    undoTurn(
        &app.history,
        &app.game
    );

    undoTurn(
        &app.history,
        &app.game
    );

    undoTurn(
        &app.history,
        &app.game
    );

    redoTurn(
        &app.history,
        &app.game
    );

    redoTurn(
        &app.history,
        &app.game
    );

    redoTurn(
        &app.history,
        &app.game
    );

    redoTurn(
        &app.history,
        &app.game
    );

    redoTurn(
        &app.history,
        &app.game
    );

    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, app.game.board.stoneIds[0] );
    TEST_ASSERT_EQUAL_INT( 0, app.game.board.stoneCounts[0] );
    TEST_ASSERT_EQUAL_INT( STONE_TYPE_NONE, app.game.board.stackTypes[0] );

    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, app.game.board.stoneIds[20] );
    TEST_ASSERT_EQUAL_INT( 1, app.game.board.stoneCounts[1] );
    TEST_ASSERT_EQUAL_INT( STONE_TYPE_STANDING, app.game.board.stackTypes[1] );
    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, app.game.board.stackIds[1] );

    TEST_ASSERT_EQUAL_INT( 4, app.history.lastRecordIdx );
    TEST_ASSERT_EQUAL_INT( 4, app.history.totalRecords );
}

void testResetTurn( void )
{
    App app = newApp();
    app.inputBuffer.lastInput = INPUT_3;
    setBoardSize( &app.game, &app.inputBuffer );

    app.command.actionType = ACTION_TYPE_PLACE;
    app.command.stoneType = STONE_TYPE_STANDING;
    app.command.playerId = PLAYER_WHITE;
    app.command.fileX = FILE_A;
    app.command.rankY = RANK_1;
    updateGame( &app );

    app.command.actionType = ACTION_TYPE_LIFT;
    app.command.fileX = FILE_A;
    app.command.rankY = RANK_1;
    updateGame( &app );

    app.command.actionType = ACTION_TYPE_DROP;

    app.command.state = COMMAND_STATE_GET_DIRECTION;

    resetTurn(
        &app.history,
        &app.game
    );

    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, app.game.board.stoneIds[0] );
    TEST_ASSERT_EQUAL_INT( 1, app.game.board.stoneCounts[0] );
    TEST_ASSERT_EQUAL_INT( STONE_TYPE_STANDING, app.game.board.stackTypes[0] );
    TEST_ASSERT_EQUAL_INT( 1, app.history.lastRecordIdx );
    TEST_ASSERT_EQUAL_INT( 1, app.history.totalRecords );

    app.command.actionType = ACTION_TYPE_LIFT;
    app.command.fileX = FILE_A;
    app.command.rankY = RANK_1;
    updateGame( &app );

    app.command.actionType = ACTION_TYPE_DROP;
    app.command.direction = DIR_RIGHT;

    app.command.state = COMMAND_STATE_GET_FIRST_DROP_AMOUNT;

    resetTurn(
        &app.history,
        &app.game
    );

    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, app.game.board.stoneIds[0] );
    TEST_ASSERT_EQUAL_INT( 1, app.game.board.stoneCounts[0] );
    TEST_ASSERT_EQUAL_INT( STONE_TYPE_STANDING, app.game.board.stackTypes[0] );
    TEST_ASSERT_EQUAL_INT( 1, app.history.lastRecordIdx );
    TEST_ASSERT_EQUAL_INT( 1, app.history.totalRecords );

    // app.command.state = COMMAND_STATE_GET_RANK_Y;
    app.command.actionType = ACTION_TYPE_LIFT;
    app.command.fileX = FILE_A;
    app.command.rankY = RANK_1;
    updateGame( &app );

    // app.command.state = COMMAND_STATE_GET_FIRST_DROP_AMOUNT;
    app.command.actionType = ACTION_TYPE_DROP;
    app.command.fileX = FILE_A;
    app.command.rankY = RANK_1;
    app.command.direction = DIR_RIGHT;
    app.command.drops = 0;
    app.command.dropCounts[0] = 0;
    updateGame( &app );

    app.command.state = COMMAND_STATE_GET_DROP_AMOUNT;

    resetTurn(
        &app.history,
        &app.game
    );

    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, app.game.board.stoneIds[0] );
    TEST_ASSERT_EQUAL_INT( 1, app.game.board.stoneCounts[0] );
    TEST_ASSERT_EQUAL_INT( STONE_TYPE_STANDING, app.game.board.stackTypes[0] );
    TEST_ASSERT_EQUAL_INT( 1, app.history.lastRecordIdx );
    TEST_ASSERT_EQUAL_INT( 1, app.history.totalRecords );
}
#endif
