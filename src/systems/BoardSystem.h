#ifndef IG20251219004302
#define IG20251219004302

#include "Board.h"
#include "PlayerId.h"
#include "StoneType.h"

/// Return new Stacks SoA
Board newBoard( void );

/**
 * @brief: Place stone on top of stack
 *
 * - Add stone affiliation
 * - Set played stone type
 * - Increase stack height
 */
Board putStoneOnStack(
    Board board,
    int const stackIdx,
    PlayerId const playerId,
    StoneType const type
);

#endif
