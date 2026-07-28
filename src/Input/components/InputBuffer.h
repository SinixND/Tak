#ifndef IG20260317235410
#define IG20260317235410

#include "CommandId.h"
#include "InputId.h"
#include "Keymap.h"

/// Store per frame user input
typedef struct InputBuffer
{
    Keymap keymap;
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
