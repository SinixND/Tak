#ifndef IG20251126094144
#define IG20251126094144

#include "Stones.h"

/// Allocate memory
Stones allocateStoneComponents(
    int const playerCount,
    int const stoneCountPerPlayer
);

/// Initialize values; Leaves stone at [0] uninitialized to enable invalid stoneId = 0
void initStones(
    Stones* stones,
    int const playerCount,
    int const stoneCountPerPlayer
);

/// Free allocated memory
void deinitStones( Stones* const stones );

#endif
