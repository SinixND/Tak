#include "StackBufferSystem.h"
#include "StackBuffer.h"
#include "StackSystem.h"
#include "StoneType.h"

StackBuffer newStackBuffer( void )
{
    StackBuffer buffer = {
        newStack(),
        STONE_TYPE_NONE
    };

    return buffer;
}
