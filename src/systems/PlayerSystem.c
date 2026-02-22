#include "PlayerSystem.h"

#include "Players.h"
#include "StoneType.h"
#include <assert.h>

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
