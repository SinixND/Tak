#ifndef IG20260317123947
#define IG20260317123947

#include "Game.h"
#include "History.h"
#include "InputBuffer.h"
#include <stdbool.h>

typedef struct App
{
    Game game;
    InputBuffer inputBuffer;
    History history;
    bool shouldClose;
} App;

#endif
