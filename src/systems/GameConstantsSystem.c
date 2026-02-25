#include "GameConstantsSystem.h"

#include "GameConstants.h"

int getBaseRegularStoneReserves( int const boardWidth )
{
    return STONE_COUNTS_REGULAR[boardWidth - BOARD_WIDTH_MIN];
}

int getBaseCapstoneReserves( int const boardWidth )
{
    return STONE_COUNTS_CAPSTONE[boardWidth - BOARD_WIDTH_MIN];
}

