#include "ReserveSystem.h"
#include "Players.h"
#include "StoneType.h"
#include "Stones.h"

int takeFromReserves(
    Players* const players,
    Stones* const stones,
    int const player,
    StoneType const type
)
{
    switch ( type )
    {
        case FLAT:
        case WALL:
        {
            --players->regularReserves[player];
            break;
        }

        case CAP:
        {
            --players->capstoneReserves[player];
            break;
        }
        default:
        {
            break;
        }
    }

    //* Get new stone index
    return stones->inPlayCount++;
}
