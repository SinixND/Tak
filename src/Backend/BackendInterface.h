#ifndef IG20260327175731
#define IG20260327175731

#include "App.h"
#include "UIData.h"

/// Context

/// Setup backend context
void setupBackend( UIData* uiData );

/// Close backend context
void closeBackend( UIData* uiData );

/// Timing

/// Delay execution for n milliseconds
void wait( int const ms );

/// Input

/// Normalize user input from backend
void pollInput( InputBuffer* const pInput );

/// Render

/// Render app state
void render( App const* const pApp );

#endif
