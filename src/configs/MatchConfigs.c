#include "MatchConfigs.h"

#include "GameConstants.h"
#include <assert.h>

MatchConfigs defineMatchConfigs( int const boardWidth )
{
    assert( boardWidth > ( BOARD_WIDTH_MIN - 1 ) );
    assert( boardWidth < ( BOARD_WIDTH_MAX + 1 ) );

    MatchConfigs constants = {
        STONE_COUNTS_REGULAR[boardWidth - BOARD_WIDTH_MIN],
        STONE_COUNTS_CAPSTONE[boardWidth - BOARD_WIDTH_MIN]
    };

    return constants;
}

int getTotalPlayerReserves( MatchConfigs const matchConfigs )
{
    return matchConfigs.regularStoneReserves + matchConfigs.capstoneReserves;
}
