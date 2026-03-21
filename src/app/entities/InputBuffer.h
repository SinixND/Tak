#ifndef IG20260317235410
#define IG20260317235410

#include "GameEvent.h"
#include "InputId.h"

typedef struct
{
    GameEvent gameEvent;
    InputId lastInput;
    char currentInput[11];
    int8_t inputLength;
} InputBuffer;

#endif
