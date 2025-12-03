#ifndef IG20251128150724
#define IG20251128150724

/**
 * @brief A board holds stacks
 */
typedef struct
{
    /// Constant size of board
    int const size;
    /// Stacks located at [(boardSize * y) + x]
    int* stacks;
} Board;

/// Initialize values;
Board initBoard( int const boardSize );

/// Free allocated memory
void deinitBoard( Board* const board );

#endif
