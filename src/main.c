#include "App.h"
#include "Demo.h"
#include "GameConstants.h"

int main( void )
{
    // TODO: Remove
    demo();

    App app = newApp( BOARD_SIZE_DEFAULT );

    setupApp();
    runApp( &app );
    closeApp();

    return 0;
}
