#ifndef IG20251203140133
#define IG20251203140133

#include <stdint.h>

/**
 * @brief Constant data for a match, depend on settings
 *
 * aka. runtime constants
 */
typedef struct
{
    /// Board width
    uint8_t boardWidth;
    /// Total stones available
    uint8_t stonesTotal : 7;
    /// Board square count
    uint8_t boardSquares : 7;
    /// Reserves per player
    uint8_t baseRegularReserves : 6;
    uint8_t baseCapstoneReserves : 2;
} MatchConfigs;

#endif
