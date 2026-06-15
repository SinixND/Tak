#ifndef IG20260224173020
#define IG20260224173020

#include "GameConstants.h"
#include "PlayerId.h"
#include "StoneTypeId.h"
#include <stdint.h>

/**
 * @brief: This is the stack being moved
 *
 * Only the top stone of a stack can have a type other than `FLAT`
 * For this stack index 0 is top
 */
typedef struct StackBuffer
{
    /// StoneId is the players Id/color
    PlayerId stoneIds[BOARD_SIZE_MAX];
    /// Active stone count in stack
    uint8_t stoneCount;
    /// Type of stack / top stone
    StoneType stackType;
} StackBuffer;

/// Return initialized object
StackBuffer newStackBuffer( void );

/**
 * @brief: Reset buffer and set stone type
 *
 * - Set buffer stone type
 * - Reset stone count to 0
 */
void resetBuffer(
    StackBuffer* const pBuffer,
    StoneType const stoneType
);

/**
 * @brief: Add stone to buffer
 *
 * - Add stone to buffer
 * - Increase stone count
 */
void appendToBuffer(
    StackBuffer* const pBuffer,
    PlayerId const playerId
);

/**
 * @brief: Remove stone from buffer
 *
 * - Decrease stone count
 */
void dropFromBuffer( StackBuffer* const pBuffer );

#endif
