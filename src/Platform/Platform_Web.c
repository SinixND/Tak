#include "PlatformInterface.h"

#ifdef PLATFORM_WEB
#include "App.h"
#include <assert.h>
#include <emscripten/emscripten.h>
#include <emscripten/html5.h>

void loop( App* const pApp )
{
    assert(
        pApp
        && "Pointer is nullptr"
    );

    emscripten_set_main_loop_arg(
        updateFrame,
        pApp,
        60 /*FPS*/,
        1 /*Simulate infinite loop*/
    );
}

#endif
