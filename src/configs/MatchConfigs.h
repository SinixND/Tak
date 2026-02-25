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
    int boardWidth;
    /// Reserves per player
    int baseRegularReserves;
    int baseCapstoneReserves;
    /// Total stones available
    int stonesTotal;
    /// Board tile count
    int boardTiles;
} MatchConfigs;

#endif
