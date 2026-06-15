#ifndef IG20251126113110
#define IG20251126113110

/**
 * @brief Constant data for the core game
 *
 * aka. compiletime constants
 */
enum
{
    /// Player count
    PLAYER_COUNT = 2,

    /// Squares per Width/Height
    BOARD_SIZE_MIN = 3,

    /// Squares per Width/Height
    BOARD_SIZE_MAX = 8,

    /// Squares per Width/Height
    BOARD_SIZE_DEFAULT = 5,

    /**
     * Maximum stacks possible in game (= squares)
     * May be increased to improve alignment for cache
     * Required for array initialization (constant size)
     */
    SQUARES_MAX = 64,

    /**
     * Maximum stones possible in game: 101 (= all regular stones + 1 capstone)
     * May be adjusted to improve alignment for cache
     * Required for array initialization (constant size)
     */
    STONES_MAX = 101,
};

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

/// Get single player reserves for regular stones
int getReservesRegular( int const boardSize );

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

/// Get single player reserves for capstones
int getReservesCapstone( int const boardSize );

/// Get max amount of stones that can form a single stack
int getStackCapacity( int const boardSize );

#endif
