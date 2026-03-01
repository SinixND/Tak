#include "BoardWidthId.h"
#include "Game.h"
#include "GameSystem.h"

int main( void )
{
    Game game = newGame( BWD_NONE );

    game = run( game );
    (void)game; // Suppress unreadVariable

    return 0;
}
