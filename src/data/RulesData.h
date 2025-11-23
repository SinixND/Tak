#ifndef IG20251126113110
#define IG20251126113110

/// Player count
static int const PLAYER_COUNT = 2;

/// Minimal board width/height
static int const BOARD_SIZE_MIN = 3;

/// Maximal board width/height
static int const BOARD_SIZE_MAX = 8;

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

#endif
