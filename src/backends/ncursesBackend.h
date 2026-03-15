#ifndef IG20260315171332
#define IG20260315171332

#include "Application.h"

void initBackend( void );
void deinitBackend( void );
Application runMainLoop( Application app );
char takeInput( char ch );
void updateGame( void );
void renderOutput( char const ch );

#endif
