#include "App.h"
#include "AppSystem.h"
#include "Game.h"
#include "GameSystem.h"
#include "MainLoopSystem.h"

int main( void )
{
    // TODO: Remove
    Game game = newGame( 0 );
    demo( &game );

    App app = newApp( 0 );

    initApp();
    runMainLoop( &app );
    closeApp();

    return 0;
}
