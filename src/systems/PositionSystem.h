#ifndef IG20251219102623
#define IG20251219102623

/**
 * @brief  Convert 2D position to array index
 *
 * Position coordinates starting from 0
 * so (0,0) matches index 0
 */
int positionToBoardIndex(
    int const x,
    int const y,
    int const boardWidth
);

#endif
