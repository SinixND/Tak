#ifndef IG20251123234852
#define IG20251123234852

/**
 * @brief Player stats
 */
typedef struct
{
    int* regularReserves;
    int* capstoneReserves;
} Players;

/// Allocate memory; Add one extra to enable invalid ID = 0
Players allocatePlayerComponents( int const playerCount );

/// Initialize values; Leaves [0] uninitialized
void initPlayers(
    Players* players,
    int const playerCount,
    int const regularReserves,
    int const capstoneReserves
);

/// Free allocated memory
void deinitPlayers( Players* const players );

#endif
