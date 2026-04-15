#ifndef IG20260322034600
#define IG20260322034600

#include "InputBuffer.h"
#include <stdbool.h>

InputBuffer newInputBuffer( void );

void appendToCurrentCommand(
    InputBuffer* const inputBuffer,
    char const ch
);

void resetCurrentCommand( InputBuffer* const inputBuffer );

/// Parse input depending on app state
/// Returns if input was valid
bool parseInputActionType( InputBuffer* const inputBuffer );
bool parseInputFileX( InputBuffer* const inputBuffer );
bool parseInputRankY( InputBuffer* const inputBuffer );
bool parseInputStoneType( InputBuffer* const inputBuffer );
bool parseInputDirection( InputBuffer* const inputBuffer );
bool parseInputFirstDropAmount( InputBuffer* const inputBuffer );
bool parseInputAmount( InputBuffer* const inputBuffer );

#endif
