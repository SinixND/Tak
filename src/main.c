#include "Application.h"
#include "ApplicationSystem.h"

int main( void )
{
    Application app = newApp();

    runApp( &app );

    return 0;
}
