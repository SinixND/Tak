#include "UI_Interface.h"

#ifdef BACKEND_NCURSES
#include "CommandId.h"
#include "UI.h"
#include "UIElement.h"
#include "UIElementId.h"
#include <assert.h>

UI newUI( void )
{
    UI ui;

    ui.elements[UIELEMENT_CHOOSE_SIZE_TEXT].x = 1;
    ui.elements[UIELEMENT_CHOOSE_SIZE_TEXT].y = 1;
    ui.elements[UIELEMENT_CHOOSE_SIZE_TEXT].width = 17;
    ui.elements[UIELEMENT_CHOOSE_SIZE_TEXT].height = 1;
    ui.elements[UIELEMENT_CHOOSE_SIZE_TEXT].commandId = COMMAND_NONE;
    ui.elements[UIELEMENT_CHOOSE_SIZE_TEXT].text = "Choose board size";

    ui.elements[UIELEMENT_CHOOSE_SIZE_3x3].x = 2;
    ui.elements[UIELEMENT_CHOOSE_SIZE_3x3].y = 3;
    ui.elements[UIELEMENT_CHOOSE_SIZE_3x3].width = 5;
    ui.elements[UIELEMENT_CHOOSE_SIZE_3x3].height = 3;
    ui.elements[UIELEMENT_CHOOSE_SIZE_3x3].commandId = COMMAND_3;
    ui.elements[UIELEMENT_CHOOSE_SIZE_3x3].text = "3x3";

    ui.elements[UIELEMENT_CHOOSE_SIZE_4x4].x = 12;
    ui.elements[UIELEMENT_CHOOSE_SIZE_4x4].y = 3;
    ui.elements[UIELEMENT_CHOOSE_SIZE_4x4].width = 5;
    ui.elements[UIELEMENT_CHOOSE_SIZE_4x4].height = 3;
    ui.elements[UIELEMENT_CHOOSE_SIZE_4x4].commandId = COMMAND_4;
    ui.elements[UIELEMENT_CHOOSE_SIZE_4x4].text = "4x4";

    ui.elements[UIELEMENT_CHOOSE_SIZE_5x5].x = 2;
    ui.elements[UIELEMENT_CHOOSE_SIZE_5x5].y = 7;
    ui.elements[UIELEMENT_CHOOSE_SIZE_5x5].width = 5;
    ui.elements[UIELEMENT_CHOOSE_SIZE_5x5].height = 3;
    ui.elements[UIELEMENT_CHOOSE_SIZE_5x5].commandId = COMMAND_5;
    ui.elements[UIELEMENT_CHOOSE_SIZE_5x5].text = "5x5";

    ui.elements[UIELEMENT_CHOOSE_SIZE_6x6].x = 12;
    ui.elements[UIELEMENT_CHOOSE_SIZE_6x6].y = 7;
    ui.elements[UIELEMENT_CHOOSE_SIZE_6x6].width = 5;
    ui.elements[UIELEMENT_CHOOSE_SIZE_6x6].height = 3;
    ui.elements[UIELEMENT_CHOOSE_SIZE_6x6].commandId = COMMAND_6;
    ui.elements[UIELEMENT_CHOOSE_SIZE_6x6].text = "6x6";

    ui.elements[UIELEMENT_CHOOSE_SIZE_7x7].x = 2;
    ui.elements[UIELEMENT_CHOOSE_SIZE_7x7].y = 11;
    ui.elements[UIELEMENT_CHOOSE_SIZE_7x7].width = 5;
    ui.elements[UIELEMENT_CHOOSE_SIZE_7x7].height = 3;
    ui.elements[UIELEMENT_CHOOSE_SIZE_7x7].commandId = COMMAND_7;
    ui.elements[UIELEMENT_CHOOSE_SIZE_7x7].text = "7x7";

    ui.elements[UIELEMENT_CHOOSE_SIZE_8x8].x = 12;
    ui.elements[UIELEMENT_CHOOSE_SIZE_8x8].y = 11;
    ui.elements[UIELEMENT_CHOOSE_SIZE_8x8].width = 5;
    ui.elements[UIELEMENT_CHOOSE_SIZE_8x8].height = 3;
    ui.elements[UIELEMENT_CHOOSE_SIZE_8x8].commandId = COMMAND_8;
    ui.elements[UIELEMENT_CHOOSE_SIZE_8x8].text = "8x8";

    ui.elements[UIELEMENT_UNDO].x = 1;
    ui.elements[UIELEMENT_UNDO].y = 1;
    ui.elements[UIELEMENT_UNDO].width = 2;
    ui.elements[UIELEMENT_UNDO].height = 2;
    ui.elements[UIELEMENT_UNDO].commandId = COMMAND_UNDO;

    ui.elements[UIELEMENT_REDO].x = 5;
    ui.elements[UIELEMENT_REDO].y = 1;
    ui.elements[UIELEMENT_REDO].width = 2;
    ui.elements[UIELEMENT_REDO].height = 2;
    ui.elements[UIELEMENT_REDO].commandId = COMMAND_REDO;

    ui.elements[UIELEMENT_RESET].x = 1;
    ui.elements[UIELEMENT_RESET].y = 4;
    ui.elements[UIELEMENT_RESET].width = 2;
    ui.elements[UIELEMENT_RESET].height = 2;
    ui.elements[UIELEMENT_RESET].commandId = COMMAND_RESET;

    ui.elements[UIELEMENT_QUIT].x = 5;
    ui.elements[UIELEMENT_QUIT].y = 4;
    ui.elements[UIELEMENT_QUIT].width = 2;
    ui.elements[UIELEMENT_QUIT].height = 2;
    ui.elements[UIELEMENT_QUIT].commandId = COMMAND_QUIT;

    ui.elements[UIELEMENT_STACK_BUFFER].x = 11;
    ui.elements[UIELEMENT_STACK_BUFFER].y = 1;
    ui.elements[UIELEMENT_STACK_BUFFER].width = 5;
    ui.elements[UIELEMENT_STACK_BUFFER].height = 5;
    ui.elements[UIELEMENT_STACK_BUFFER].commandId = COMMAND_NONE;

    ui.elements[UIELEMENT_INFO].x = 0;
    ui.elements[UIELEMENT_INFO].y = 6;
    ui.elements[UIELEMENT_INFO].width = 18;
    ui.elements[UIELEMENT_INFO].height = 3;
    ui.elements[UIELEMENT_INFO].commandId = COMMAND_CYCLE_STONE_TYPE;

    ui.elements[UIELEMENT_ACTIVE_PLAYER].x = 0;
    ui.elements[UIELEMENT_ACTIVE_PLAYER].y = 9;
    ui.elements[UIELEMENT_ACTIVE_PLAYER].width = 17;
    ui.elements[UIELEMENT_ACTIVE_PLAYER].height = 1;
    ui.elements[UIELEMENT_ACTIVE_PLAYER].commandId = COMMAND_CYCLE_STONE_TYPE;

    ui.elements[UIELEMENT_COMMAND].x = 0;
    ui.elements[UIELEMENT_COMMAND].y = 10;
    ui.elements[UIELEMENT_COMMAND].width = 16;
    ui.elements[UIELEMENT_COMMAND].height = 1;
    ui.elements[UIELEMENT_COMMAND].commandId = COMMAND_CYCLE_STONE_TYPE;

    ui.elements[UIELEMENT_HISTORY].x = 0;
    ui.elements[UIELEMENT_HISTORY].y = 11;
    ui.elements[UIELEMENT_HISTORY].width = 8;
    ui.elements[UIELEMENT_HISTORY].height = 1;
    ui.elements[UIELEMENT_HISTORY].commandId = COMMAND_NONE;

    ui.elements[UIELEMENT_BOARD].x = 20;
    ui.elements[UIELEMENT_BOARD].y = 1;
    ui.elements[UIELEMENT_BOARD].width = -1;
    ui.elements[UIELEMENT_BOARD].height = -1;
    ui.elements[UIELEMENT_BOARD].commandId = COMMAND_POSITION;

    return ui;
}

void updateUI(
    UI* const pUI,
    int const boardSize
)
{
    assert( pUI && "Pointer is invalid" );

    pUI->elements[UIELEMENT_BOARD].width = ( boardSize * 4 ) + 1;
    pUI->elements[UIELEMENT_BOARD].height = ( boardSize * 4 ) + 1;
}

#endif
