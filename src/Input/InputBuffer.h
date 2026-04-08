#ifndef IG20260317235410
#define IG20260317235410

#include "InputId.h"

/// Store per frame user input
typedef struct InputBuffer
{
    InputId keyboard;
} InputBuffer;

/// Return initialized InputBuffer object
InputBuffer newInputBuffer( void );

#endif
