#ifndef IG20260320234908
#define IG20260320234908

#include "InputBuffer.h"
#include <stdbool.h>

InputBuffer newInputBuffer( void );

/// Handle input depending on app state

/// Returns if input was valid
bool parseInputForAction( InputBuffer* const inputBuffer );
bool parseInputForFileX( InputBuffer* const inputBuffer );
bool parseInputForRankY( InputBuffer* const inputBuffer );
bool parseInputForStoneType( InputBuffer* const inputBuffer );
bool parseInputForDirection( InputBuffer* const inputBuffer );
/// Get first drop amount (0-8)
bool parseInputForFirstDropAmount( InputBuffer* const inputBuffer );
/// Get drop amount (1-8)
bool parseInputForAmount( InputBuffer* const inputBuffer );

#endif
