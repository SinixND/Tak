#include "DirectionId.h"

int getOffsetX( DirectionId const direction )
{
    switch ( direction )
    {
        case DIR_LEFT:
            return -1;

        case DIR_RIGHT:
            return 1;

        default:
            return 0;
    }
}

int getOffsetY( DirectionId const direction )
{
    switch ( direction )
    {
        case DIR_DOWN:
            return -1;

        case DIR_UP:
            return 1;

        default:
            return 0;
    }
}
