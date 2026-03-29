#ifndef IG20260327150921
#define IG20260327150921

#include "App.h"

/// Setup before running the application loop
void setupApp( void );

/// Run main application loop, ticking frames
void runApp( App* const  pApp );

/// Clean up before closing the application
void closeApp( void );

/// Return initialized history object
App newApp( int const boardWidth );

/// Tick next frame
void updateFrame( App* const  pApp );

#endif
