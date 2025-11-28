#ifndef IG20251128165244
#define IG20251128165244

#include "Board.h"

/// Allocate memory; Add one extra to enable invalid ID = 0
Board allocateBoardComponents( int const boardSize );

/// Initialize values;
void initBoard(
    Board* board,
    int const boardSize
);

/// Free allocated memory
void deinitBoard( Board* const board );

#endif
