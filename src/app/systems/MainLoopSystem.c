#include "MainLoopSystem.h"

#include "App.h"
#include "AppSystem.h"
#include "InputPollingSystem.h"
#include "RenderSystem.h"

void runMainLoop( App* const app )
{
    renderStaticContent( app );

    while ( !app->shoudClose )
    {
        //* Have dedicated funciton called in the loop for emscripten
        processFrame( app );
    }
}

void processFrame( App* const app )
{
    renderApp( app );
    getInput( &app->inputBuffer );
    updateApp( app );
}
