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

    Players players;

    int initRegularReserves = getBaseRegularStoneReserves( boardWidth );
    int initCapstoneReserves = getBaseCapstoneReserves( boardWidth );

    //* Init player values
    for ( int idx = 0; idx < PLAYER_COUNT; ++idx )
    {
        players.stonesInPlay[idx] = 0;
        players.reservesRegular[idx] = initRegularReserves;
        players.reservesCapstone[idx] = initCapstoneReserves;
    }

    return players;
}

void takeFromReserves(
    Players* const players,
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
                players->reservesRegular[playerId] > 0
                && "No reserves left"
            );

            --players->reservesRegular[playerId];

            break;
        }

        case STONE_TYPE_CAP:
        {
            assert(
                players->reservesCapstone[playerId] > 0
                && "No reserves left"
            );

            --players->reservesCapstone[playerId];

            break;
        }
    }

    ++players->stonesInPlay[playerId];
}

void returnToReserves(
    Players* const players,
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
            ++players->reservesRegular[playerId];

            break;
        }

        case STONE_TYPE_CAP:
        {
            ++players->reservesCapstone[playerId];

            break;
        }
    }

    --players->stonesInPlay[playerId];
}

