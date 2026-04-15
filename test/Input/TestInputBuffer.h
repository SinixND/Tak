#ifndef IG20260415171218
#define IG20260415171218

#include "InputBuffer.h"
#include "InputId.h"
#include <unity.h>

void testNewInputBuffer( void )
{
    InputBuffer inputBuffer = newInputBuffer();

    TEST_ASSERT_EQUAL_INT( INPUT_NONE, inputBuffer.keyboard );
}

#endif
