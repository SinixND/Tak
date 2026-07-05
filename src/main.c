#include "App.h"

int main( void )
{
    App app = newApp();

    setupApp( &app );
    runApp( &app );
    closeApp( &app );

    return 0;
}
