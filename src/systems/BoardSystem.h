#ifndef IG20251219004302
#define IG20251219004302

#include "Board.h"
#include "PlayerId.h"
#include "StoneType.h"

/// Return new, empty board object
Board newBoard( int const boardWidth );

/** 
* @brief; Add new stone to a square
*
* - Set stack type
* - Add playerId to stones
* - Increase stack count
 */
void putOntoStack(
    Board* const pBoard,
    PlayerId const playerId,
    int const squareIdx,
    StoneType const stoneType
);

/** 
* @brief; Remove n stones from a square
*
* - Decrease stack count
* - Set stack type
 */
void takeFromStack(
    Board* const pBoard,
    int const squareIdx,
    int const stoneCount
);

#endif
