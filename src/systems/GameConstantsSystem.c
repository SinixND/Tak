#include "GameConstantsSystem.h"

#include "GameConstants.h"

int getBaseRegularStoneReserves( int const boardWidth )
{
    return RESERVES_BASE_REGULAR[boardWidth - BOARD_WIDTH_MIN];
}

int getBaseCapstoneReserves( int const boardWidth )
{
    return RESERVES_BASE_CAPSTONE[boardWidth - BOARD_WIDTH_MIN];
}

