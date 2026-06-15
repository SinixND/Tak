#include "App.h"

int main( void )
{
    App app = newApp();

    setupApp();
    runApp( &app );
    closeApp();

    return 0;
}
