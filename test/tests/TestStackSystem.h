#ifndef IG20260104182516
#define IG20260104182516

#include "Stack.h"
#include "StackSystem.h"
#include <unity.h>

void testNewStack( void )
{
    //* EXECUTE
    Stack stack = newStack();

    //* VERIFY
    TEST_ASSERT_EQUAL_INT( (int)NO_STONE, stack.type );
    TEST_ASSERT_EQUAL_INT( 0, stack.height );
    TEST_ASSERT_EQUAL_INT( 0, stack.affiliations[0] );
    TEST_ASSERT_EQUAL_INT( 0, stack.affiliations[44] );
}

#endif
