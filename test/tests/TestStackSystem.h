#ifndef IG20260104182517
#define IG20260104182517

#include "GameConstants.h"
#include "PlayerId.h"
#include "Stack.h"
#include "StackSystem.h"
#include <unity.h>

void testNewStack( void )
{
    Stack stack = newStack();

    TEST_ASSERT_EQUAL_INT( 0, stack.counts );
    TEST_ASSERT_EQUAL_INT( PLAYER_NONE, stack.stoneIds[0] );
    TEST_ASSERT_EQUAL_INT( PLAYER_NONE, stack.stoneIds[STONES_MAX - 1] );
}

