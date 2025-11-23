#ifndef IG20251126111707
#define IG20251126111707

#include "Players.h"

/// Allocate memory
Players allocatePlayerComponents( int const playerCount );

/// Initialize values
void initPlayers(
    Players* players,
    int const playerCount,
    int const regularReserves,
    int const capstoneReserves
);

/// Free allocated memory
void deinitPlayers( Players* const players );

#endif
