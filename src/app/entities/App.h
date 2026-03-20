#ifndef IG20260317123947
#define IG20260317123947

#include "AppState.h"
#include "Game.h"
#include "InputBuffer.h"
#include <stdbool.h>

typedef struct
{
    Game game;
    InputBuffer inputBuffer;
    AppState state;
    bool shoudClose;
} App;

#endif
