#include "Reserves.h"

#include "GameConstants.h"
#include "PlayerId.h"
#include "StoneTypeId.h"
#include <assert.h>

Reserves newReserves( int const boardSize )
{
    assert(
        ( boardSize >= BOARD_SIZE_MIN )
        && ( boardSize <= BOARD_SIZE_MAX )
        && "Board size invalid"
    );

    Reserves reserves = { 0 };

    int regularReserves = getReservesRegular( boardSize );
    int capstoneReserves = getReservesCapstone( boardSize );

    /// Init player values
    for ( int idx = 0; idx < PLAYER_COUNT; ++idx )
    {
        reserves.regular[idx] = regularReserves;
        reserves.capstone[idx] = capstoneReserves;
    }

    return reserves;
}

void takeFromReserves(
    Reserves* const pReserves,
    PlayerId const playerId,
    StoneType const stoneType
)
{
    assert(
        pReserves
        && "Pointer is nullptr"
    );

    assert(
        ( playerId == PLAYER_WHITE
          || playerId == PLAYER_BLACK )
        && "PlayerId invalid"
    );

    assert(
        ( stoneType != STONE_TYPE_NONE )
        && "PlayerId invalid"
    );

    switch ( stoneType )
    {
        case STONE_TYPE_FLAT:
        case STONE_TYPE_STANDING:
        {
            assert(
                pReserves->regular[playerId] > 0
                && "No reserves left"
            );

            --pReserves->regular[playerId];

            return;
        }

        case STONE_TYPE_CAP:
        {
            assert(
                pReserves->capstone[playerId] > 0
                && "No reserves left"
            );

            --pReserves->capstone[playerId];

            return;
        }

        default:
        {
            assert( !"StoneType is required" );
            return;
        }
    }
}

void returnToReserves(
    Reserves* const pReserves,
    PlayerId const playerId,
    StoneType const stoneType
)
{
    assert(
        pReserves
        && "Pointer is nullptr"
    );

    assert(
        ( playerId == PLAYER_WHITE || playerId == PLAYER_BLACK )
        && "PlayerId invalid"
    );

    switch ( stoneType )
    {
        case STONE_TYPE_FLAT:
        case STONE_TYPE_STANDING:
        {
            ++pReserves->regular[playerId];

            return;
        }

        case STONE_TYPE_CAP:
        {
            ++pReserves->capstone[playerId];

            return;
        }

        default:
        {
            assert( !"StoneType is required" );
            return;
        }
    }
}

