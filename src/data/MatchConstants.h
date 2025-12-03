#ifndef IG20251203140133
#define IG20251203140133

/**
 * @brief Constant data for a match, depend on settings
 *
 * aka. runtime constants
 */
typedef struct
{
    /// Reserves per player
    int const regularStoneReserves;
    int const capstoneReserves;
} MatchConstants;

MatchConstants defineMatchConstants( int const boardSize );

/// Returns total reserves per player
int getTotalReserves( MatchConstants const matchConstants );

#endif
