#ifndef IG20261025191308
#define IG20261025191308

#include "UI.h"

/// Set initial UIElements
UI newUI( void );

/// Update dynamic UIElement members
void updateUI(
    UI* const pUI,
    int const boardSize
);

#endif
