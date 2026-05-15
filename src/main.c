#include "App.h"
#include "Demo.h"
#include "GameConstants.h"

int main( void )
{
    App app = newApp();

    // TODO: Remove
    demo( &app );

    setupApp();
    runApp( &app );
    closeApp();

    return 0;
}
