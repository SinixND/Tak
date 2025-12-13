#include "GameSettings.h"

GameSettings getDefaultSettings( void )
{
    GameSettings settings = {
        .boardSize = 5
    };

    return settings;
}
