#ifndef IG20251128150724
#define IG20251128150724

/**
 * @brief A board holds stacks
 */
typedef struct
{
    /// Constant count of board tiles
    int const tileCount;
    /// Stacks located at [(y * boardWidth ) + x]
    int* stackIdxs;
} Board;

/// Allocate memory and initialize values
Board initBoard( int const boardWidth );

/// Free allocated memory
void deinitBoard( Board* const board );

#endif
