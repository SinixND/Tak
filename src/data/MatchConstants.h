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

/// Valid boardWidths: 3 to 8
MatchConstants defineMatchConstants( int const boardWidth );

/// Returns total reserves per player
int getTotalPlayerReserves( MatchConstants const matchConstants );

#endif
