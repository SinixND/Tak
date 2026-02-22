#ifndef IG20251203140133
#define IG20251203140133

/**
 * @brief Constant data for a match, depend on settings
 *
 * aka. runtime constants
 */
typedef struct
{
    /// Board width
    int const boardWidth;
    /// Reserves per player
    int const regularStonePlayerReserves;
    int const capstonePlayerReserves;
    /// Total stones available
    int const stonesTotal;
    /// Board tile count
    int const boardTiles;
} MatchConfigs;

/// Valid boardWidths: 3 to 8
MatchConfigs defineMatchConfigs( int const boardWidth );

/// Default configuration
MatchConfigs getDefaultMatchConfigs( void );

/// Returns total reserves per player
int getTotalPlayerReserves( MatchConfigs const matchConfigs );

#endif
