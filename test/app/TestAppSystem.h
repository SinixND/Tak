#ifndef IG20260327191049
#define IG20260327191049

#include "App.h"
#include "AppSystem.h"
#include "GameConstants.h"
#include "InputId.h"
#include <unity.h>

void testNewApp( void )
{
    App app = newApp( 0 );

    TEST_ASSERT_EQUAL_INT( BOARD_WIDTH_DEFAULT, app.game.board.width );
    TEST_ASSERT_EQUAL_INT( INPUT_NONE, app.inputBuffer.keyboard );
    TEST_ASSERT_EQUAL_INT( false, app.shouldClose );

    app = newApp( 3 );

    TEST_ASSERT_EQUAL_INT( 3, app.game.board.width );

    app = newApp( 8 );

    TEST_ASSERT_EQUAL_INT( 8, app.game.board.width );
}

#endif
