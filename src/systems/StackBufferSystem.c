#include "StackBufferSystem.h"

#include "StackBuffer.h"
#include "StackSystem.h"
#include "StoneType.h"
#include <assert.h>

StackBuffer newStackBuffer( void )
{
    StackBuffer buffer = {
        newStack(),
        .type = STONE_TYPE_NONE
    };

    return buffer;
}
