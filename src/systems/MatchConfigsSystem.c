#include "MatchConfigsSystem.h"

#include "GameConstants.h"
#include "GameConstantsSystem.h"
#include <assert.h>

MatchConfigs getMatchConfigs( BoardWidthId const boardWidthId )
{
    assert(
        ( boardWidthId >= BOARD_WIDTH_MIN )
        && "Board width value too small"
    );

    assert(
        ( boardWidthId <= BOARD_WIDTH_MAX )
        && "Board width value too big"
    );

    MatchConfigs configs = {
        .boardWidthId = boardWidthId,
        .baseRegularReserves = RESERVES_BASE_REGULAR[boardWidthId - BOARD_WIDTH_MIN],
        .baseCapstoneReserves = RESERVES_BASE_CAPSTONE[boardWidthId - BOARD_WIDTH_MIN],
        .stonesTotal = 2 * getBaseRegularStoneReserves( boardWidthId ) + 2 * getBaseCapstoneReserves( boardWidthId ),
        .boardSquares = boardWidthId * boardWidthId,
    };

    return configs;
}
