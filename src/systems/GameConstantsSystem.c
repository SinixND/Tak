#include "GameConstantsSystem.h"

#include "GameConstants.h"

int getBaseRegularStoneReserves( BoardWidthId const boardWidthId )
{
    return RESERVES_BASE_REGULAR[boardWidthId - BOARD_WIDTH_MIN];
}

int getBaseCapstoneReserves( BoardWidthId const boardWidthId )
{
    return RESERVES_BASE_CAPSTONE[boardWidthId - BOARD_WIDTH_MIN];
}

