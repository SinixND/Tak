#include "ReservesSystem.h"

#include "GameConstants.h"
#include "PlayerId.h"
#include "Reserves.h"
#include "StoneTypeId.h"
#include <assert.h>

Reserves newReserves( int const boardWidth )
{
    assert(
        ( boardWidth >= BOARD_WIDTH_MIN )
        && "Board width value too small"
    );

    assert(
        ( boardWidth <= BOARD_WIDTH_MAX )
        && "Board width value too big"
    );

    Reserves reserves = { 0 };

    int regularReserves = RESERVES_BASE_REGULAR[boardWidth - BOARD_WIDTH_MIN];
    int capstoneReserves = RESERVES_BASE_CAPSTONE[boardWidth - BOARD_WIDTH_MIN];

    //* Init player values
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
        ( playerId == PLAYER_WHITE || playerId == PLAYER_BLACK )
        && "Invalid playerId"
    );

    assert(
        ( stoneType != STONE_TYPE_NONE )
        && "Invalid playerId"
    );

    switch ( stoneType )
    {
        default:
        {
            assert( !"StoneType is required" );

            break;
        }

        case STONE_TYPE_FLAT:
        case STONE_TYPE_STANDING:
        {
            assert(
                pReserves->regular[playerId] > 0
                && "No reserves left"
            );

            --pReserves->regular[playerId];

            break;
        }

        case STONE_TYPE_CAP:
        {
            assert(
                pReserves->capstone[playerId] > 0
                && "No reserves left"
            );

            --pReserves->capstone[playerId];

            break;
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
        ( playerId == PLAYER_WHITE || playerId == PLAYER_BLACK )
        && "Invalid playerId"
    );

    switch ( stoneType )
    {
        default:
        {
            assert( !"StoneType is required" );

            break;
        }

        case STONE_TYPE_FLAT:
        case STONE_TYPE_STANDING:
        {
            ++pReserves->regular[playerId];

            break;
        }

        case STONE_TYPE_CAP:
        {
            ++pReserves->capstone[playerId];

            break;
        }
    }
}

