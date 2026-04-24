#include "StackBuffer.h"

#include "PlayerId.h"
#include "StoneTypeId.h"
#include <assert.h>

StackBuffer newStackBuffer( void )
{
    StackBuffer buffer = {
        .stackType = STONE_TYPE_NONE,
        .stoneCount = 0,
    };

    for ( int stoneIdx = 0; stoneIdx < BOARD_SIZE_MAX; ++stoneIdx )
    {
        buffer.stoneIds[stoneIdx] = PLAYER_NONE;
    }

    return buffer;
}

void resetBuffer(
    StackBuffer* const pBuffer,
    StoneType const stoneType
)
{
    assert(
        pBuffer
        && "Pointer is nullptr"
    );

    assert(
        stoneType != STONE_TYPE_NONE
        && "Invalid stoneId"
    );

    pBuffer->stackType = stoneType;
    pBuffer->stoneCount = 0;
}

void appendToBuffer(
    StackBuffer* const pBuffer,
    PlayerId const playerId
)
{
    assert(
        pBuffer
        && "Pointer is nullptr"
    );

    assert(
        ( playerId == PLAYER_WHITE || playerId == PLAYER_BLACK )
        && "Invalid playerId"
    );

    /// Add playerId
    pBuffer->stoneIds[pBuffer->stoneCount] = playerId;

    /// Increase stack count
    ++pBuffer->stoneCount;
}

void dropFromBuffer( StackBuffer* const pBuffer )
{
    assert(
        pBuffer->stoneCount > 0
        && "Cannot drop from empty buffer"
    );

    /// Decrease stack count
    --pBuffer->stoneCount;

    /// Set stack type
    if ( pBuffer->stoneCount < 1 )
    {
        pBuffer->stackType = STONE_TYPE_NONE;
    }
}
