#ifndef IG20260705032717
#define IG20260705032717

#include "GameScreenElementId.h"
#include "SelectScreenElementId.h"
#include "UIElement.h"

typedef struct UI
{
    UIElement selectScreenElements[SELECT_SCREEN_ELEMENT_COUNT];
    UIElement gameScreenElements[GAME_SCREEN_ELEMENT_COUNT];
} UI;

#endif
