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

    ui.uiElements[UI_ELEMENT_STACK_BUFFER].uiElementId = UI_ELEMENT_STACK_BUFFER;
    ui.uiElements[UI_ELEMENT_STACK_BUFFER].x = 0;
    ui.uiElements[UI_ELEMENT_STACK_BUFFER].y = 0;
    ui.uiElements[UI_ELEMENT_STACK_BUFFER].width = 11;
    ui.uiElements[UI_ELEMENT_STACK_BUFFER].height = 6;
    ui.uiElements[UI_ELEMENT_STACK_BUFFER].commandId = COMMAND_NONE;

    ui.uiElements[UI_ELEMENT_UNDO].uiElementId = UI_ELEMENT_UNDO;
    ui.uiElements[UI_ELEMENT_UNDO].x = 12;
    ui.uiElements[UI_ELEMENT_UNDO].y = 1;
    ui.uiElements[UI_ELEMENT_UNDO].width = 2;
    ui.uiElements[UI_ELEMENT_UNDO].height = 2;
    ui.uiElements[UI_ELEMENT_UNDO].commandId = COMMAND_UNDO;

    ui.uiElements[UI_ELEMENT_REDO].uiElementId = UI_ELEMENT_REDO;
    ui.uiElements[UI_ELEMENT_REDO].x = 16;
    ui.uiElements[UI_ELEMENT_REDO].y = 1;
    ui.uiElements[UI_ELEMENT_REDO].width = 2;
    ui.uiElements[UI_ELEMENT_REDO].height = 2;
    ui.uiElements[UI_ELEMENT_REDO].commandId = COMMAND_REDO;

    ui.uiElements[UI_ELEMENT_RESET].uiElementId = UI_ELEMENT_RESET;
    ui.uiElements[UI_ELEMENT_RESET].x = 12;
    ui.uiElements[UI_ELEMENT_RESET].y = 4;
    ui.uiElements[UI_ELEMENT_RESET].width = 2;
    ui.uiElements[UI_ELEMENT_RESET].height = 2;
    ui.uiElements[UI_ELEMENT_RESET].commandId = COMMAND_RESET;

    ui.uiElements[UI_ELEMENT_QUIT].uiElementId = UI_ELEMENT_QUIT;
    ui.uiElements[UI_ELEMENT_QUIT].x = 16;
    ui.uiElements[UI_ELEMENT_QUIT].y = 4;
    ui.uiElements[UI_ELEMENT_QUIT].width = 2;
    ui.uiElements[UI_ELEMENT_QUIT].height = 2;
    ui.uiElements[UI_ELEMENT_QUIT].commandId = COMMAND_QUIT;

    ui.uiElements[UI_ELEMENT_INFO].uiElementId = UI_ELEMENT_INFO;
    ui.uiElements[UI_ELEMENT_INFO].x = 0;
    ui.uiElements[UI_ELEMENT_INFO].y = 6;
    ui.uiElements[UI_ELEMENT_INFO].width = 18;
    ui.uiElements[UI_ELEMENT_INFO].height = 3;
    ui.uiElements[UI_ELEMENT_INFO].commandId = COMMAND_CYCLE_STONE_TYPE;

    ui.uiElements[UI_ELEMENT_ACTIVE_PLAYER].uiElementId = UI_ELEMENT_ACTIVE_PLAYER;
    ui.uiElements[UI_ELEMENT_ACTIVE_PLAYER].x = 0;
    ui.uiElements[UI_ELEMENT_ACTIVE_PLAYER].y = 9;
    ui.uiElements[UI_ELEMENT_ACTIVE_PLAYER].width = 17;
    ui.uiElements[UI_ELEMENT_ACTIVE_PLAYER].height = 1;
    ui.uiElements[UI_ELEMENT_ACTIVE_PLAYER].commandId = COMMAND_CYCLE_STONE_TYPE;

    ui.uiElements[UI_ELEMENT_COMMAND].uiElementId = UI_ELEMENT_COMMAND;
    ui.uiElements[UI_ELEMENT_COMMAND].x = 0;
    ui.uiElements[UI_ELEMENT_COMMAND].y = 10;
    ui.uiElements[UI_ELEMENT_COMMAND].width = 16;
    ui.uiElements[UI_ELEMENT_COMMAND].height = 1;
    ui.uiElements[UI_ELEMENT_COMMAND].commandId = COMMAND_CYCLE_STONE_TYPE;

    ui.uiElements[UI_ELEMENT_HISTORY].uiElementId = UI_ELEMENT_HISTORY;
    ui.uiElements[UI_ELEMENT_HISTORY].x = 0;
    ui.uiElements[UI_ELEMENT_HISTORY].y = 11;
    ui.uiElements[UI_ELEMENT_HISTORY].width = 8;
    ui.uiElements[UI_ELEMENT_HISTORY].height = 1;
    ui.uiElements[UI_ELEMENT_HISTORY].commandId = COMMAND_NONE;

    ui.uiElements[UI_ELEMENT_BOARD].uiElementId = UI_ELEMENT_BOARD;
    ui.uiElements[UI_ELEMENT_BOARD].x = 19;
    ui.uiElements[UI_ELEMENT_BOARD].y = 0;
    ui.uiElements[UI_ELEMENT_BOARD].width = -1;
    ui.uiElements[UI_ELEMENT_BOARD].height = -1;
    ui.uiElements[UI_ELEMENT_BOARD].commandId = COMMAND_POSITION;

    return ui;
}

void updateUI(
    UI* const pUI,
    int const boardSize
)
{
    assert( pUI && "Pointer is invalid" );
    pUI->uiElements[UI_ELEMENT_BOARD].width = ( boardSize * 4 ) + 3;
    pUI->uiElements[UI_ELEMENT_BOARD].height = ( boardSize * 4 ) + 3;
}

#endif
