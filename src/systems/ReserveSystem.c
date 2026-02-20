#include "ReserveSystem.h"

#include "StoneType.h"
#include <assert.h>

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
            assert( 0 && "StoneType is required" );
            break;
        }
    }

    //* Get index for taken stone before incrementing
    return ( *inPlayCount )++;
}
