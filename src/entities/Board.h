#ifndef IG20251128150724
#define IG20251128150724

/**
 * @brief A board holds stacks
 */
typedef struct
{
    /// Constant count of board tiles per side
    int const width;
    /// Stacks located at tile [(y * boardWidth ) + x]
    int* stackIdxs;
} Board;

/// Allocate memory and initialize values
Board initBoard( int const boardWidth );

/// Free allocated memory
void deinitBoard( Board* const board );

#endif
