#ifndef IG20260327191049
#define IG20260327191049

#include "App.h"
#include "InputId.h"
#include <unity.h>

void testSetBoardSize( void )
{
    App app = newApp();

    app.inputBuffer.lastInput = INPUT_2;
    TEST_ASSERT_EQUAL_INT( false, setBoardSize( &app ) );

    app.inputBuffer.lastInput = INPUT_3;
    TEST_ASSERT_EQUAL_INT( true, setBoardSize( &app ) );
    TEST_ASSERT_EQUAL_INT( 3, app.game.board.size );

    app.inputBuffer.lastInput = INPUT_4;
    TEST_ASSERT_EQUAL_INT( true, setBoardSize( &app ) );
    TEST_ASSERT_EQUAL_INT( 4, app.game.board.size );

    app.inputBuffer.lastInput = INPUT_5;
    TEST_ASSERT_EQUAL_INT( true, setBoardSize( &app ) );
    TEST_ASSERT_EQUAL_INT( 5, app.game.board.size );

    app.inputBuffer.lastInput = INPUT_SPACE;
    TEST_ASSERT_EQUAL_INT( true, setBoardSize( &app ) );
    TEST_ASSERT_EQUAL_INT( BOARD_SIZE_DEFAULT, app.game.board.size );

    app.inputBuffer.lastInput = INPUT_6;
    TEST_ASSERT_EQUAL_INT( true, setBoardSize( &app ) );
    TEST_ASSERT_EQUAL_INT( 6, app.game.board.size );

    app.inputBuffer.lastInput = INPUT_7;
    TEST_ASSERT_EQUAL_INT( true, setBoardSize( &app ) );
    TEST_ASSERT_EQUAL_INT( 7, app.game.board.size );

    app.inputBuffer.lastInput = INPUT_8;
    TEST_ASSERT_EQUAL_INT( true, setBoardSize( &app ) );
    TEST_ASSERT_EQUAL_INT( 8, app.game.board.size );
}

#endif
