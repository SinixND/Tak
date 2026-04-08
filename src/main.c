#include "App.h"
#include "DemoSystem.h"

int main( void )
{
    // TODO: Remove
    demo();

    App app = newApp( 0 );

    setupApp();
    runApp( &app );
    closeApp();

    return 0;
}
