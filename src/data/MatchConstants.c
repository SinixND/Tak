#include "MatchConstants.h"

#include "GameConstants.h"
#include <assert.h>

MatchConstants defineMatchConstants( int boardSize )
{
    assert( ( boardSize > ( BOARD_SIZE_MIN - 1 ) ) && "[ERROR] boardSize too small" );
    assert( ( boardSize < ( BOARD_SIZE_MAX + 1 ) ) && "[ERROR] boardSize too big" );

    MatchConstants constants = {
        STONE_COUNTS_REGULAR[boardSize - BOARD_SIZE_MIN],
        STONE_COUNTS_CAPSTONE[boardSize - BOARD_SIZE_MIN]
    };

    return constants;
}

int getTotalReserves( MatchConstants const matchConstants )
{
    return matchConstants.regularStoneReserves + matchConstants.capstoneReserves;
}
