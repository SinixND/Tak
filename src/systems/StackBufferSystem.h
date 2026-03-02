#ifndef IG20260224223032
#define IG20260224223032

#include "StackBuffer.h"

StackBuffer newStackBuffer( void );

StackBuffer appendToBottom(
    StackBuffer buffer,
    PlayerId const playerId
);

StackBuffer dropFromBottom( StackBuffer buffer );

#endif
