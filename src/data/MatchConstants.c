#include "MatchConstants.h"

#include "GameConstants.h"
#include <assert.h>

MatchConstants defineMatchConstants( int const boardWidth )
{
    assert( boardWidth > ( BOARD_WIDTH_MIN - 1 ) );
    assert( boardWidth < ( BOARD_WIDTH_MAX + 1 ) );

    MatchConstants constants = {
        STONE_COUNTS_REGULAR[boardWidth - BOARD_WIDTH_MIN],
        STONE_COUNTS_CAPSTONE[boardWidth - BOARD_WIDTH_MIN]
    };

    return constants;
}

int getTotalReserves( MatchConstants const matchConstants )
{
    return matchConstants.regularStoneReserves + matchConstants.capstoneReserves;
}
