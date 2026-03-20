#ifndef IG20260320081726
#define IG20260320081726

#include "App.h"
#include "InputBuffer.h"

/// Handle input independent of app state
void handleGlobalInput( App* const app );

/// Handle input depending on app state
void handleStateInput( App* const app );

void parseInputForAction( InputBuffer* const inputBuffer );
void parseInputForFileX( InputBuffer* const inputBuffer );
void parseInputForRankY( InputBuffer* const inputBuffer );
void parseInputForStoneType( InputBuffer* const inputBuffer );
void parseInputForDirection( InputBuffer* const inputBuffer );

#endif
