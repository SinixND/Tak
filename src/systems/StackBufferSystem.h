#ifndef IG20260224223032
#define IG20260224223032

#include "StackBuffer.h"

/// Return initialized StackBuffer object
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
