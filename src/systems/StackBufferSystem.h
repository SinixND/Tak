#ifndef IG20260224223032
#define IG20260224223032

#include "StackBuffer.h"

StackBuffer newStackBuffer( void );

void resetStackBuffer(
    StackBuffer* const pBuffer,
    PlayerId const playerId,
    StoneType const stoneType
);

#endif
