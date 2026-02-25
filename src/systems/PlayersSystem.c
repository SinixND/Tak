#include "PlayersSystem.h"

#include "GameConstantsSystem.h"
#include "Players.h"
#include "StoneType.h"
#include <assert.h>

Players newPlayers( int const boardWidth )
{
    assert( ( boardWidth >= BOARD_WIDTH_MIN ) && "Board width value too small" );
    assert( ( boardWidth <= (int)BOARD_WIDTH_MAX ) && "Board width value too big" );

    Players players = { 0 };

    int initRegularReserves = getBaseRegularStoneReserves( boardWidth );
    int initCapstoneReserves = getBaseCapstoneReserves( boardWidth );

    //* Init player values
    for ( int idx = 0; idx < PLAYER_COUNT; ++idx )
    {
        players.stonesInPlay[idx] = 0;
        players.regularReserves[idx] = initRegularReserves;
        players.capstoneReserves[idx] = initCapstoneReserves;
    }

    return players;
}

Players takeFromReserves(
    Players players,
    int const playerIdx,
    StoneType const type
)
{
    switch ( type )
    {
        case STONE_TYPE_FLAT:
        case STONE_TYPE_WALL:
        {
            assert( players.regularReserves[playerIdx] > 0 && "No reserves left" );
            --players.regularReserves[playerIdx];
            break;
        }

        case STONE_TYPE_CAP:
        {
            assert( players.capstoneReserves[playerIdx] > 0 && "No reserves left" );
            --players.capstoneReserves[playerIdx];
            break;
        }

        default:
        {
            assert( 0 && "StoneType is required" );
            break;
        }
    }

    ++players.stonesInPlay[playerIdx];

    return players;
}
