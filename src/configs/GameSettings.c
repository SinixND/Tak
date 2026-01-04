#include "GameSettings.h"

GameSettings getDefaultSettings( void )
{
    GameSettings settings = {
        .boardWidth = 5
    };

    return settings;
}
