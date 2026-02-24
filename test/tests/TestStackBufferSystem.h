#ifndef IG20260104182516
#define IG20260104182516

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
    TEST_ASSERT_EQUAL_INT( NO_STONE, buffer.type );
    TEST_ASSERT_EQUAL_INT( 0, buffer.stack.height );
    TEST_ASSERT_EQUAL_INT( 0, buffer.stack.affiliations[0] );
    TEST_ASSERT_EQUAL_INT( 0, buffer.stack.affiliations[44] );
}

#endif
