#ifndef IG20260224223032
#define IG20260224223032

#include "StackBuffer.h"

/// Return new StackBuffer object
StackBuffer newStackBuffer( void );

/// Reset buffer to new type and first stone (=playerId)
void resetStackBuffer(
    StackBuffer* const pBuffer,
    PlayerId const playerId,
    StoneType const stoneType
);

/// Add stone to buffer ("below")
void appendToBuffer(
    StackBuffer* const pBuffer,
    PlayerId const playerId
);

#endif
