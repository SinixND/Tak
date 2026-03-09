#include "StackBufferSystem.h"

#include "PlayerId.h"
#include "StackBuffer.h"
#include "StoneType.h"
#include <assert.h>

StackBuffer newStackBuffer( void )
{
    StackBuffer buffer = { 0 };

    for ( int stoneIdx = 0; stoneIdx < BOARD_WIDTH_MAX; ++stoneIdx )
    {
        buffer.stoneIds[stoneIdx] = PLAYER_NONE;
    }

    buffer.type = STONE_TYPE_NONE;
    buffer.count = 0;

    return buffer;
}

void setBufferStoneType(
    StackBuffer* const pBuffer,
    StoneType const stoneType
)
{
    assert(
        stoneType != STONE_TYPE_NONE
        && "Invalid stoneId"
    );

    pBuffer->type = stoneType;
    pBuffer->count = 0;

    // pBuffer->stoneIds[0] = playerId;
}

void appendToBuffer(
    StackBuffer* const pBuffer,
    PlayerId const playerId
)
{
    assert(
        ( playerId == PLAYER_WHITE || playerId == PLAYER_BLACK )
        && "Invalid playerId"
    );

    //* Add playerId
    pBuffer->stoneIds[pBuffer->count] = playerId;

    //* Increase stack count
    ++pBuffer->count;
}

void dropFromBuffer( StackBuffer* const pBuffer )
{
    assert(
        pBuffer->count > 0
        && "Cannot drop from empty buffer"
    );

    //* Decrease stack count
    --pBuffer->count;
}
