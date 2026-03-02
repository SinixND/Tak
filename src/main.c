#include "Game.h"
#include "GameSystem.h"

int main( void )
{
    Game game = newGame( 0 );

    game = run( game );
    (void)game; // Suppress unreadVariable

    return 0;
}
