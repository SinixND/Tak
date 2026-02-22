#ifndef IG20251126113110
#define IG20251126113110

/**
 * @brief Size of initial player reserves
 * Regular stones, by board size
 */
static int const STONE_COUNTS_REGULAR[] = {
    10, // Size: 3x3
    15, // Size: 4x4
    21, // Size: 5x5
    30, // Size: 6x6
    40, // Size: 7x7
    50, // Size: 8x8
};

/**
 * @brief Size of initial player reserves
 * Capstones, by board size
 */
static int const STONE_COUNTS_CAPSTONE[] = {
    0, // Size: 3x3
    0, // Size: 4x4
    1, // Size: 5x5
    1, // Size: 6x6
    2, // Size: 7x7
    2, // Size: 8x8
};

/**
 * @brief Constant data for the core game
 *
 * aka. compiletime constants
 */
enum
{
    /// Player count
    PLAYER_COUNT = 2,
    /// Index 0 for invalid player
    PLAYER_ARRAY_SIZE = PLAYER_COUNT + 1,

    /// Minimal board width/height
    BOARD_WIDTH_MIN = 3,

    /// Maximal board width/height
    BOARD_WIDTH_MAX = 8,

    /// Default board width/height
    BOARD_WIDTH_DEFAULT = 5,

    /* Maximum stacks possible in game
     * =: BOARD_WIDTH_MAX * BOARD_WIDTH_MAX + 1 // Max boardtiles + 1 temp stack
     */
    STACKS_MAX = 65,
    /// Index 0 for invalid stack
    STACKS_ARRAY_SIZE = STACKS_MAX + 1,

    /* Maximum stones possible in game
     * =: PLAYER_COUNT * ( STONE_COUNTS_REGULAR[5] + STONE_COUNTS_CAPSTONE[5] )
     */
    STONES_MAX = 104,
};

#endif
