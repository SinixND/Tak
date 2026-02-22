#include "GameConstantsSystem.h"

#include "GameConstants.h"

int getRegularStoneCount( int const boardWidth )
{
    return STONE_COUNTS_REGULAR[boardWidth - BOARD_WIDTH_MIN];
}

int getCapstoneCount( int const boardWidth )
{
    return STONE_COUNTS_CAPSTONE[boardWidth - BOARD_WIDTH_MIN];
}

