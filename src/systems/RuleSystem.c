#include "RuleSystem.h"

#include "RulesData.h"
#include <assert.h>

int getPlayerInitialRegularStoneCount( int boardSize )
{
    assert( boardSize > ( BOARD_SIZE_MIN - 1 ) );
    assert( boardSize < ( BOARD_SIZE_MAX + 1 ) );

    return STONE_COUNTS_REGULAR[boardSize - BOARD_SIZE_MIN];
}

int getPlayerInitialCapstoneCount( int boardSize )
{
    assert( boardSize > ( BOARD_SIZE_MIN - 1 ) );
    assert( boardSize < ( BOARD_SIZE_MAX + 1 ) );

    return STONE_COUNTS_CAPSTONE[boardSize - BOARD_SIZE_MIN];
}
