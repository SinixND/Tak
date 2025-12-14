#include "ReserveSystem.h"

#include "StoneType.h"

int takeFromReserves(
    int* const regularReserves,
    int* const capstoneReserves,
    int* const inPlayCount,
    int const player,
    StoneType const type
)
{
    switch ( type )
    {
        case FLAT:
        case WALL:
        {
            --regularReserves[player];
            break;
        }

        case CAP:
        {
            --capstoneReserves[player];
            break;
        }
        default:
        {
            break;
        }
    }

    //* Get new stone index
    return ( *inPlayCount )++;
}
