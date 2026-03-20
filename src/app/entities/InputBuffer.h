#ifndef IG20260317235410
#define IG20260317235410

#include "GameEvent.h"
#include "InputId.h"

typedef struct
{
    GameEvent gameEvent;
    InputId lastInput;
} InputBuffer;

#endif
