#include "App.h"
#include "AppSystem.h"
#include "Game.h"
#include "GameSystem.h"
#include "MainLoopSystem.h"

int main( void )
{
    Game game = newGame( 0 );
    demo( &game );

    App app = newApp( 0 );

    initApp();
    runMainLoop( &app );
    deinitApp();

    return 0;
}
