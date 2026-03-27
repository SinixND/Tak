#include "App.h"
#include "AppSystem.h"
#include "GameSystem.h"

int main( void )
{
    App app = newApp( 0 );

    // TODO: Remove
    demo( &app.game );

    setupApp();
    runApp( &app );
    closeApp();

    return 0;
}
