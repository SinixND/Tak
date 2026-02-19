#ifndef IG20251221041510
#define IG20251221041510

#include "StoneType.h"

/// Returns number/index of the stone taken
int takeFromReserves(
    int* const regularReserves,
    int* const capstoneReserves,
    int* const inPlayCount,
    int const player,
    StoneType const type
);

#endif
