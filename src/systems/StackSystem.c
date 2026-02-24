#include "StackSystem.h"

#include "StoneType.h"
#include <assert.h>

Stack newStack( void )
{
    Stack stack = {
        NO_STONE,
        0,
        { 0 }
    };

    return stack;
}

