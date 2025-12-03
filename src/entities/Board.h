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

/// Initialize values;
Board initBoard( int const boardSize);

/// Free allocated memory
void deinitBoard( Board* const board );

#endif
