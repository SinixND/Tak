#ifndef IG20251126094144
#define IG20251126094144

#include "Stones.h"

/// Allocate memory; Add one extra to enable invalid ID = 0
Stones allocateStoneComponents( int const stoneCount);

/// Initialize values; Leaves [0] uninitialized
void initStones(
    Stones* stones,
    int const playerCount,
    int const stoneCountPerPlayer
);

/// Free allocated memory
void deinitStones( Stones* const stones );

#endif
