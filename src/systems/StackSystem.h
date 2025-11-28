#ifndef IG20251126093805
#define IG20251126093805

#include "Stacks.h"

/// Allocate memory; Add one extra to enable invalid ID = 0
Stacks allocateStackComponents( int const stackCount );

/// Initialize values; Leaves [0] uninitialized
void initStacks(
    Stacks* stacks,
    int const boardSize
);

/// Free allocated memory
void deinitStacks( Stacks* const stacks );

#endif
