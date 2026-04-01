#ifndef IG20260327175731
#define IG20260327175731

#include "App.h"
#include "InputId.h"

//* Context
/// Setup backend context
void setupBackend( void );
/// Close backend context
void closeBackend( void );

//* Timing
/// Run backend loop
void loopBackend( App* const  pApp );

//* Input
/// Normalize user input from backend
void pollInput( InputBuffer* const  pInput );

#endif
