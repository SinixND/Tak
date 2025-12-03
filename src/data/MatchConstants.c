#include "MatchConstants.h"

#include "GameConstants.h"
#include <assert.h>

MatchConstants defineMatchConstants(int boardSize)
{
    assert( boardSize > ( BOARD_SIZE_MIN - 1 ) );
    assert( boardSize < ( BOARD_SIZE_MAX + 1 ) );

    MatchConstants constants = {
        STONE_COUNTS_REGULAR[boardSize - BOARD_SIZE_MIN],
        STONE_COUNTS_CAPSTONE[boardSize - BOARD_SIZE_MIN]
    } ;

    return constants;
}

int getTotalReserves(MatchConstants const matchConstants)
{
    return matchConstants.regularStoneReserves + matchConstants.capstoneReserves;

}