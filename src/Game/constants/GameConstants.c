#include "GameConstants.h"

#include <assert.h>

int getReservesRegular( int const boardSize )
{
    assert(
            ( boardSize >= BOARD_SIZE_MIN )
            && ( boardSize <= BOARD_SIZE_MAX )
            && "Board size invalid"
    );

    return RESERVES_BASE_REGULAR[boardSize - BOARD_SIZE_MIN];
}

int getReservesCapstone( int const boardSize )
{
    assert(
            ( boardSize >= BOARD_SIZE_MIN )
            && ( boardSize <= BOARD_SIZE_MAX )
            && "Board size invalid"
    );

    return RESERVES_BASE_CAPSTONE[boardSize - BOARD_SIZE_MIN];
}

int getStackCapacity( int const boardSize )
{
    assert(
            ( boardSize >= BOARD_SIZE_MIN )
            && ( boardSize <= BOARD_SIZE_MAX )
            && "Board size invalid"
    );

    return PLAYER_COUNT * RESERVES_BASE_REGULAR[boardSize - BOARD_SIZE_MIN]
           // Can only have one capstone per stack
           + (int)( 0 != RESERVES_BASE_CAPSTONE[boardSize - BOARD_SIZE_MIN] );
}
