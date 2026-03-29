#include "App.h"
#include "AppSystem.h"
#include "DemoSystem.h"

int main( void )
{
    App app = newApp( 0 );

    // TODO: Remove
    demo( &app );

    setupApp();
    runApp( &app );
    closeApp();

    return 0;
}
