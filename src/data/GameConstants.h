#ifndef IG20251126113110
#define IG20251126113110

#include "BoardWidthId.h"

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
    BOARD_WIDTH_MIN = BWD_3,

    /// Maximal board width/height
    /// equals max moved stone count
    BOARD_WIDTH_MAX = BWD_8,

    /// Default board width/height
    BOARD_WIDTH_DEFAULT = BWD_5,

    /**
     * Maximum stacks possible in game
     * May be adjusted to improve alignment for cache
     */
    STACKS_MAX = 64,

    /**
     * Maximum stones possible in game: 104
     * May be adjusted to improve alignment for cache
     */
    STONES_MAX = 104,

    /// Undo/Redo history size
    HISTORY_SIZE = 100,
};

#endif
