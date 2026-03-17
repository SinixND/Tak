#ifndef IG20260224173020
#define IG20260224173020

#include "GameConstants.h"
#include "PlayerId.h"
#include "StoneType.h"
#include <stdint.h>

/**
 * @brief: This is the stack being moved
 *
 * Only the top stone of a stack can have a type other than `FLAT`
 * For this stack index 0 is top
 */
typedef struct
{
    /// StoneId is the players Id/color
    PlayerId stoneIds[BOARD_WIDTH_MAX];
    /// Active stone count in stack
    uint8_t stoneCount;
    /// Type of stack / top stone
    StoneType stoneType;
} StackBuffer;

#endif
