#ifndef IG20260327175731
#define IG20260327175731

#include "App.h"

/// Context

/// Setup backend context
void setupBackend( void );

/// Close backend context
void closeBackend( void );

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
