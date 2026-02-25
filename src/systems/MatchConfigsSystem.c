#include "MatchConfigsSystem.h"

#include "GameConstants.h"
#include "GameConstantsSystem.h"
#include <assert.h>

MatchConfigs getMatchConfigs( int const boardWidth )
{
    assert( ( boardWidth >= BOARD_WIDTH_MIN ) && "Board width value too small" );
    assert( ( boardWidth <= BOARD_WIDTH_MAX ) && "Board width value too big" );

    MatchConfigs configs = {
        .boardWidth = boardWidth,
        .baseRegularReserves = RESERVES_BASE_REGULAR[boardWidth - BOARD_WIDTH_MIN],
        .baseCapstoneReserves = RESERVES_BASE_CAPSTONE[boardWidth - BOARD_WIDTH_MIN],
        .stonesTotal = 2 * getBaseRegularStoneReserves( boardWidth ) + 2 * getBaseCapstoneReserves( boardWidth ),
        .boardTiles = boardWidth * boardWidth,
    };

    return configs;
}
