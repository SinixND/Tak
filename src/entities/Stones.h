#ifndef IG20251124141518
#define IG20251124141518

#include <assert.h>

/**
 * @brief SoA: A stone piece that belongs to a player
 *
 * It can be placed or moved on the board
 */
typedef struct
{
    /// Stones in play
    int inPlay;
    /// Owning player, either '0' or '1'
    int* affiliations;
    /// Index of stone below/covered by stoneId
    int* captives;
} Stones;

/// Initialize values; Leaves [0] uninitialized
Stones initStones(
    int const playerCount,
    int const stoneCountPerPlayer
);

/// Free allocated memory
void deinitStones( Stones* const stones );

#endif

