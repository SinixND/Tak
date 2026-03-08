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

void resetStackBuffer(
    StackBuffer* const pBuffer,
    PlayerId const playerId,
    StoneType const stoneType
)
{
    assert(
        ( playerId == PLAYER_WHITE || playerId == PLAYER_BLACK )
        && "Invalid playerId"
    );

    assert(
        stoneType != STONE_TYPE_NONE
        && "Invalid stoneId"
    );

    newStackBuffer();

    pBuffer->type = stoneType;
    pBuffer->count = 1;

    pBuffer->stoneIds[0] = playerId;
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

    //* Remove stoneId
    pBuffer->stoneIds[pBuffer->count] = PLAYER_NONE;

    //* Set to none if count > 0
    pBuffer->type = STONE_TYPE_NONE + ( ( pBuffer->type - STONE_TYPE_NONE ) & -( pBuffer->count > 0 ) );
}
