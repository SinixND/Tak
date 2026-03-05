#ifndef IG20251126113110
#define IG20251126113110

/**
 * @brief Size of initial player reserves
 * Regular stones, by board size
 */
static int const RESERVES_BASE_REGULAR[] = {
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
static int const RESERVES_BASE_CAPSTONE[] = {
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

    /// Minimal board width/height
    BOARD_WIDTH_MIN = 3,

    /// Maximal board width/height
    /// equals max moved stone count
    BOARD_WIDTH_MAX = 8,

    /// Default board width/height
    BOARD_WIDTH_DEFAULT = 5,

    /**
     * Maximum stacks possible in game (= squares)
     * May be adjusted to improve alignment for cache
     */
    SQUARES_MAX = 64,

    /**
     * Maximum stones possible in game: 104 (= all regular stones + 1 capstone)
     * May be adjusted to improve alignment for cache
     */
    STONES_MAX = 101,

    /// Undo/Redo history size
    HISTORY_SIZE = 100,
};

#endif
