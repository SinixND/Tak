#ifndef IG20260104182516
#define IG20260104182516

#include "GameConstants.h"
#include "PlayerId.h"
#include "Stack.h"
#include "StackBuffer.h"
#include "StackBufferSystem.h"
#include "StoneType.h"
#include <unity.h>

void testNewStackBuffer( void )
{
    //* EXECUTE
    StackBuffer buffer = newStackBuffer();

    //* VERIFY

    TEST_ASSERT_EQUAL_INT( STONE_TYPE_NONE, buffer.type );
    TEST_ASSERT_EQUAL_INT( 0, buffer.stack.count );
    TEST_ASSERT_EQUAL_INT( PLAYER_NONE, buffer.stack.affiliations[0] );
    TEST_ASSERT_EQUAL_INT( PLAYER_NONE, buffer.stack.affiliations[STONES_MAX - 1] );
}

#endif
