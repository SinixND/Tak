#include "PlayersSystem.h"

#include "GameConstantsSystem.h"
#include "Players.h"
#include "StoneType.h"
#include <assert.h>

Players newPlayers( int const boardWidth )
{
    assert( ( boardWidth >= (int)BOARD_WIDTH_MIN ) && "Board width value too small" );
    assert( ( boardWidth <= (int)BOARD_WIDTH_MAX ) && "Board width value too big" );

    Players players = { 0 };

    //* Init invalid player values
    players.stonesInPlay[0] = 0;
    players.regularReserves[0] = 0;
    players.capstoneReserves[0] = 0;

    //* Init player values
    for ( int playerIdx = 1; playerIdx <= PLAYER_COUNT; ++playerIdx )
    {
        players.stonesInPlay[playerIdx] = 0;
        players.regularReserves[playerIdx] = getRegularStoneCount( boardWidth );
        players.capstoneReserves[playerIdx] = getCapstoneCount( boardWidth );
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
        case FLAT:
        case WALL:
        {
            assert( players.regularReserves[playerIdx] > 0 && "No reserves left" );
            --players.regularReserves[playerIdx];
            break;
        }

        case CAP:
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
