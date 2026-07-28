#ifndef IG20260317235410
#define IG20260317235410

#include "CommandId.h"
#include "InputId.h"
#include "Mappings.h"

/// Store per frame user input
typedef struct InputBuffer
{
    Mappings mappings;
    InputId lastInput;
    float position[2];
} InputBuffer;

/// Return initialized object
InputBuffer newInputBuffer( void );

/// Get context dependent command input
CommandId getCommandId(
    InputBuffer const* const pInputBuffer,
    ContextId const contextId
);

#endif
