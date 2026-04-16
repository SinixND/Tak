#ifndef IG20260317235410
#define IG20260317235410

#include "InputId.h"
#include "PlayerId.h"

/// Store per frame user input
typedef struct InputBuffer
{
    PlayerId playerId;
    InputId keyboard;
} InputBuffer;

/// Return initialized InputBuffer object
InputBuffer newInputBuffer( void );

#endif
