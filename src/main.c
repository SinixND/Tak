#include "Game.h"
#include "GameSystem.h"

int main( void )
{
    Game game = newGame( 0 );

    game = run( game );

    return 0;
}
