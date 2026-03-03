#include "PlayersSystem.h"

#include "GameConstantsSystem.h"
#include "PlayerId.h"
#include "Players.h"
#include "StoneType.h"
#include <assert.h>

Players newPlayers( int const boardWidth )
{
    assert(
        ( boardWidth >= BOARD_WIDTH_MIN )
        && "Board width value too small"
    );

    assert(
        ( boardWidth <= BOARD_WIDTH_MAX )
        && "Board width value too big"
    );

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
    PlayerId const playerId,
    StoneType const type
)
{
    assert(
        ( playerId == PLAYER_WHITE || playerId == PLAYER_BLACK )
        && "Invalid playerId"
    );

    switch ( type )
    {
        case STONE_TYPE_FLAT:
        case STONE_TYPE_STANDING:
        {
            assert(
                players.regularReserves[playerId] > 0
                && "No reserves left"
            );

            --players.regularReserves[playerId];

            break;
        }

        case STONE_TYPE_CAP:
        {
            assert(
                players.capstoneReserves[playerId] > 0
                && "No reserves left"
            );

            --players.capstoneReserves[playerId];

            break;
        }

        default:
        {
            assert( !"StoneType is required" );

            break;
        }
    }

    ++players.stonesInPlay[playerId];

    return players;
}
