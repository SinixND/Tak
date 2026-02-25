#include "MatchConfigsSystem.h"

#include "GameConstants.h"
#include "GameConstantsSystem.h"
#include <assert.h>

MatchConfigs getMatchConfigs( int const boardWidth )
{
    assert( ( boardWidth >= (int)BOARD_WIDTH_MIN ) && "Board width value too small" );
    assert( ( boardWidth <= (int)BOARD_WIDTH_MAX ) && "Board width value too big" );

    MatchConfigs configs = {
        .boardWidth = boardWidth,
        .regularStonePlayerReserves = STONE_COUNTS_REGULAR[boardWidth - BOARD_WIDTH_MIN],
        .capstonePlayerReserves = STONE_COUNTS_CAPSTONE[boardWidth - BOARD_WIDTH_MIN],
        .stonesTotal = 2 * getBaseRegularStoneReserves( boardWidth ) + 2 * getBaseCapstoneReserves( boardWidth ),
        .boardTiles = boardWidth * boardWidth,
    };

    return configs;
}
