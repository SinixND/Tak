#include "Game.h"

#include "GameSystem.h"
#include "PlayerActionsSystem.h"
#include "PlayerId.h"
#include "StoneType.h"
#include "unity.h"

void testPlayStone( void )
{
    //* SETUP
    Game game = newGame( 0 );

    //*EXECUTE
    game = playStone(
        game,
        PLAYER_WHITE,
        0,
        0,
        STONE_TYPE_FLAT
    );

    //* VERIFY
    TEST_ASSERT_EQUAL_INT( 20, game.players.regularReserves[PLAYER_WHITE] );
    TEST_ASSERT_EQUAL_INT( 1, game.board.stacks[0].height );
    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, game.board.stacks[0].affiliations[0] );
    TEST_ASSERT_EQUAL_INT( PLAYER_NONE, game.board.stacks[0].affiliations[1] );
    TEST_ASSERT_EQUAL_INT( STONE_TYPE_FLAT, game.board.types[0] );

    //*EXECUTE
    game = playStone(
        game,
        PLAYER_BLACK,
        1,
        0,
        STONE_TYPE_WALL
    );

    //* VERIFY
    TEST_ASSERT_EQUAL_INT( 20, game.players.regularReserves[PLAYER_BLACK] );
    TEST_ASSERT_EQUAL_INT( 1, game.board.stacks[1].height );
    TEST_ASSERT_EQUAL_INT( PLAYER_BLACK, game.board.stacks[1].affiliations[0] );
    TEST_ASSERT_EQUAL_INT( PLAYER_NONE, game.board.stacks[0].affiliations[1] );
    TEST_ASSERT_EQUAL_INT( STONE_TYPE_WALL, game.board.types[1] );

    //*EXECUTE
    game = playStone(
        game,
        PLAYER_WHITE,
        3,
        0,
        STONE_TYPE_CAP
    );

    //* VERIFY
    TEST_ASSERT_EQUAL_INT( 0, game.players.capstoneReserves[PLAYER_WHITE] );
    TEST_ASSERT_EQUAL_INT( 1, game.board.stacks[3].height );
    TEST_ASSERT_EQUAL_INT( PLAYER_WHITE, game.board.stacks[3].affiliations[0] );
    TEST_ASSERT_EQUAL_INT( PLAYER_NONE, game.board.stacks[3].affiliations[1] );
    TEST_ASSERT_EQUAL_INT( STONE_TYPE_CAP, game.board.types[3] );
}
