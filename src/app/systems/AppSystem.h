#ifndef IG20260327150921
#define IG20260327150921

#include "App.h"

void setupApp( void );
void runApp( App* const app );
void closeApp( void );

App newApp( int const boardWidth );

void updateFrame(App* const app);

#endif