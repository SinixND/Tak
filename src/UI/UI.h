#ifndef IG20260705032717
#define IG20260705032717

#include "GameScreenElementId.h"
#include "SelectScreenElementId.h"
#include "UIElement.h"

typedef struct UI
{
    UIElement selectScreenElements[SELECT_SCREEN_ELEMENT_COUNT];
    UIElement gameScreenElements[GAME_SCREEN_ELEMENT_COUNT];

    /// Not used for ncurses
    float windowWidth;
    float windowHeight;
} UI;

/// Set initial UIElements
UI newUI( void );

/// Update dynamic UIElement members
void updateUI(
    UI* const pUI,
    int const boardSize
);

#endif
