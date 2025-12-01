#ifndef IG20251128150724
#define IG20251128150724

/**
 * @brief A board holds stacks
 */
typedef struct
{
    /// Stacks located at [(boardSize * y) + x]
    int* stacks;
} Board;

/// Allocate memory; Add one extra to enable invalid ID = 0
Board allocateBoardComponents( int const boardSize );

/// Initialize values;
void initBoard(
    Board* board,
    int const boardSize
);

/// Free allocated memory
void deinitBoard( Board* const board );

#endif
