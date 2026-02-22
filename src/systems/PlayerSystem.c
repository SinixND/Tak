#include "PlayerSystem.h"

#include "GameConstantsSystem.h"
#include "Players.h"
#include "StoneType.h"
#include <assert.h>

Players newPlayers( int const boardWidth )
{
    assert( ( boardWidth >= (int)BOARD_WIDTH_MIN ) && "Board width value too small" );
    assert( ( boardWidth <= (int)BOARD_WIDTH_MAX ) && "Board width value too big" );

    Players players;

    //* Init invalid player values
    players.stonesInPlay[0] = 0;
    players.regularReserves[0] = 0;
    players.capstoneReserves[0] = 0;

    //* Init player values
    for ( int i = 1; i < PLAYER_COUNT; ++i )
    {
        players.stonesInPlay[i] = 0;
        players.regularReserves[i] = getRegularStoneCount( boardWidth );
        players.capstoneReserves[i] = getCapstoneCount( boardWidth );
    }

    return players;
}

Players takeFromReserves(
    Players players,
    int const player,
    StoneType const type
)
{
    switch ( type )
    {
        case FLAT:
        case WALL:
        {
            --players.regularReserves[player];
            break;
        }

        case CAP:
        {
            --players.capstoneReserves[player];
            break;
        }

        default:
        {
            assert( 0 && "StoneType is required" );
            break;
        }
    }

    players.stonesInPlay[player]++;

    return players;
}
