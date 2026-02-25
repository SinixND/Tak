#ifndef IG20260104182517
#define IG20260104182517

#include "GameConstants.h"
#include "PlayerId.h"
#include "Stack.h"
#include "StackSystem.h"
#include <unity.h>

void testNewStack( void )
{
    //* EXECUTE
    Stack stack = newStack();

    //* VERIFY
    TEST_ASSERT_EQUAL_INT( 0, stack.height );
    TEST_ASSERT_EQUAL_INT( PLAYER_NONE, stack.affiliations[0] );
    TEST_ASSERT_EQUAL_INT( PLAYER_NONE, stack.affiliations[STONES_MAX - 1] );
}

#endif
