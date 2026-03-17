#include "MainLoopSystem.h"

#include "App.h"
#include "InputBufferSystem.h"
#include "RenderSystem.h"
#include "UpdateSystem.h"

void runMainLoop( App* const app )
{
    while ( !app->shoudClose )
    {
        //* Have dedicated funciton called in the loop for emscripten
        processFrame( app );
    }
}

void processFrame( App* const app )
{
    handleInput( app );
    updateApp( app );
    renderApp( app );
}
