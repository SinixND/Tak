#ifndef IG20260327175731
#define IG20260327175731

#include "App.h"

//* Context
/// Setup backend context
void setupBackend( void );
/// Close backend context
void closeBackend( void );

//* Timing
/// Important: Calls `void updateFrame(App* const pApp)`
void loopBackend( App* const pApp );

//* Input
/// Normalize user input from backend
void pollInput( InputBuffer* const pInput );

//* Render
/// Render static application content
void renderStatic( App* const pApp );

/// Render dynamic application content
void renderDynamic( App* const pApp );

#endif
