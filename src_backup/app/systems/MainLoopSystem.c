#include "MainLoopSystem.h"

#include "App.h"
#include "AppSystem.h"
#include "InputPollingSystem.h"
#include "RenderSystem.h"

void runApp( App* const app )
{
    //* Run everything once for proper initialization
    renderStaticContent( app );
    renderApp( app );

    while ( !app->shoudClose )
    {
        //* Have dedicated funciton called in the loop for emscripten
        processFrame( app );
    }
}

void processFrame( App* const app )
{
    getInput( &app->inputBuffer );
    updateApp( app );
    renderApp( app );
}
