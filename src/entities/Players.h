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

/// Initialize values; Leaves [0] uninitialized
Players initPlayers(
    int const playerCount,
    int const regularReserves,
    int const capstoneReserves
);

/// Free allocated memory
void deinitPlayers( Players* const players );

#endif
