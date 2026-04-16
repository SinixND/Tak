#ifndef IG20260327191049
#define IG20260327191049

#include "App.h"
#include "GameConstants.h"
#include <unity.h>

void testNewApp( void )
{
    int const ARR[] = { BOARD_SIZE_DEFAULT, 3, 4, 5, 6, 7, 8 };
    int const SIZE = sizeof( ARR ) / sizeof( *ARR );

    App app = newApp( BOARD_SIZE_DEFAULT );

    for ( int i = 0; i < SIZE; ++i )
    {
        app = newApp( ARR[i] );
        TEST_ASSERT_EQUAL_INT( ARR[i], app.game.board.size );
    }
}

#endif
