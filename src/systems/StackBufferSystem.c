#include "StackBufferSystem.h"
#include "StackBuffer.h"
#include "StackSystem.h"
#include "StoneType.h"

StackBuffer newStackBuffer( void )
{
    StackBuffer buffer = {
        newStack(),
        NO_STONE
    };

    return buffer;
}
