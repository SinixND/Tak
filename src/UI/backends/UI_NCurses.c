#include "UI_Interface.h"

#ifdef BACKEND_NCURSES
#include "CommandId.h"
#include "UI.h"
#include <assert.h>

UI newUI( void )
{
    UI ui;

    ui.selectScreenElements[UIELEMENT_CHOOSE_SIZE].x = 1;
    ui.selectScreenElements[UIELEMENT_CHOOSE_SIZE].y = 1;
    ui.selectScreenElements[UIELEMENT_CHOOSE_SIZE].width = 17;
    ui.selectScreenElements[UIELEMENT_CHOOSE_SIZE].height = 1;
    ui.selectScreenElements[UIELEMENT_CHOOSE_SIZE].commandId = COMMAND_NONE;
    ui.selectScreenElements[UIELEMENT_CHOOSE_SIZE].text = "Choose board size";

    ui.selectScreenElements[UIELEMENT_3x3].x = 2;
    ui.selectScreenElements[UIELEMENT_3x3].y = 3;
    ui.selectScreenElements[UIELEMENT_3x3].width = 5;
    ui.selectScreenElements[UIELEMENT_3x3].height = 3;
    ui.selectScreenElements[UIELEMENT_3x3].commandId = COMMAND_3;
    ui.selectScreenElements[UIELEMENT_3x3].text = "3x3";

    ui.selectScreenElements[UIELEMENT_4x4].x = 12;
    ui.selectScreenElements[UIELEMENT_4x4].y = 3;
    ui.selectScreenElements[UIELEMENT_4x4].width = 5;
    ui.selectScreenElements[UIELEMENT_4x4].height = 3;
    ui.selectScreenElements[UIELEMENT_4x4].commandId = COMMAND_4;
    ui.selectScreenElements[UIELEMENT_4x4].text = "4x4";

    ui.selectScreenElements[UIELEMENT_5x5].x = 2;
    ui.selectScreenElements[UIELEMENT_5x5].y = 7;
    ui.selectScreenElements[UIELEMENT_5x5].width = 5;
    ui.selectScreenElements[UIELEMENT_5x5].height = 3;
    ui.selectScreenElements[UIELEMENT_5x5].commandId = COMMAND_5;
    ui.selectScreenElements[UIELEMENT_5x5].text = "5x5";

    ui.selectScreenElements[UIELEMENT_6x6].x = 12;
    ui.selectScreenElements[UIELEMENT_6x6].y = 7;
    ui.selectScreenElements[UIELEMENT_6x6].width = 5;
    ui.selectScreenElements[UIELEMENT_6x6].height = 3;
    ui.selectScreenElements[UIELEMENT_6x6].commandId = COMMAND_6;
    ui.selectScreenElements[UIELEMENT_6x6].text = "6x6";

    ui.selectScreenElements[UIELEMENT_7x7].x = 2;
    ui.selectScreenElements[UIELEMENT_7x7].y = 11;
    ui.selectScreenElements[UIELEMENT_7x7].width = 5;
    ui.selectScreenElements[UIELEMENT_7x7].height = 3;
    ui.selectScreenElements[UIELEMENT_7x7].commandId = COMMAND_7;
    ui.selectScreenElements[UIELEMENT_7x7].text = "7x7";

    ui.selectScreenElements[UIELEMENT_8x8].x = 12;
    ui.selectScreenElements[UIELEMENT_8x8].y = 11;
    ui.selectScreenElements[UIELEMENT_8x8].width = 5;
    ui.selectScreenElements[UIELEMENT_8x8].height = 3;
    ui.selectScreenElements[UIELEMENT_8x8].commandId = COMMAND_8;
    ui.selectScreenElements[UIELEMENT_8x8].text = "8x8";

    ui.gameScreenElements[UIELEMENT_UNDO].x = 1;
    ui.gameScreenElements[UIELEMENT_UNDO].y = 0;
    ui.gameScreenElements[UIELEMENT_UNDO].width = 2;
    ui.gameScreenElements[UIELEMENT_UNDO].height = 2;
    ui.gameScreenElements[UIELEMENT_UNDO].commandId = COMMAND_UNDO;

    ui.gameScreenElements[UIELEMENT_REDO].x = 5;
    ui.gameScreenElements[UIELEMENT_REDO].y = 0;
    ui.gameScreenElements[UIELEMENT_REDO].width = 2;
    ui.gameScreenElements[UIELEMENT_REDO].height = 2;
    ui.gameScreenElements[UIELEMENT_REDO].commandId = COMMAND_REDO;

    ui.gameScreenElements[UIELEMENT_RESET].x = 1;
    ui.gameScreenElements[UIELEMENT_RESET].y = 3;
    ui.gameScreenElements[UIELEMENT_RESET].width = 2;
    ui.gameScreenElements[UIELEMENT_RESET].height = 2;
    ui.gameScreenElements[UIELEMENT_RESET].commandId = COMMAND_RESET;

    ui.gameScreenElements[UIELEMENT_QUIT].x = 5;
    ui.gameScreenElements[UIELEMENT_QUIT].y = 3;
    ui.gameScreenElements[UIELEMENT_QUIT].width = 2;
    ui.gameScreenElements[UIELEMENT_QUIT].height = 2;
    ui.gameScreenElements[UIELEMENT_QUIT].commandId = COMMAND_QUIT;

    ui.gameScreenElements[UIELEMENT_STACK_BUFFER].x = 11;
    ui.gameScreenElements[UIELEMENT_STACK_BUFFER].y = 0;
    ui.gameScreenElements[UIELEMENT_STACK_BUFFER].width = 5;
    ui.gameScreenElements[UIELEMENT_STACK_BUFFER].height = 5;
    ui.gameScreenElements[UIELEMENT_STACK_BUFFER].commandId = COMMAND_NONE;

    ui.gameScreenElements[UIELEMENT_INFO].x = 0;
    ui.gameScreenElements[UIELEMENT_INFO].y = 6;
    ui.gameScreenElements[UIELEMENT_INFO].width = 18;
    ui.gameScreenElements[UIELEMENT_INFO].height = 3;
    ui.gameScreenElements[UIELEMENT_INFO].commandId = COMMAND_CYCLE_STONE_TYPE;

    ui.gameScreenElements[UIELEMENT_ACTIVE_PLAYER].x = 0;
    ui.gameScreenElements[UIELEMENT_ACTIVE_PLAYER].y = 9;
    ui.gameScreenElements[UIELEMENT_ACTIVE_PLAYER].width = 17;
    ui.gameScreenElements[UIELEMENT_ACTIVE_PLAYER].height = 1;
    ui.gameScreenElements[UIELEMENT_ACTIVE_PLAYER].commandId = COMMAND_CYCLE_STONE_TYPE;

    ui.gameScreenElements[UIELEMENT_COMMAND].x = 0;
    ui.gameScreenElements[UIELEMENT_COMMAND].y = 10;
    ui.gameScreenElements[UIELEMENT_COMMAND].width = 16;
    ui.gameScreenElements[UIELEMENT_COMMAND].height = 1;
    ui.gameScreenElements[UIELEMENT_COMMAND].commandId = COMMAND_CYCLE_STONE_TYPE;

    ui.gameScreenElements[UIELEMENT_HISTORY].x = 0;
    ui.gameScreenElements[UIELEMENT_HISTORY].y = 11;
    ui.gameScreenElements[UIELEMENT_HISTORY].width = 8;
    ui.gameScreenElements[UIELEMENT_HISTORY].height = 1;
    ui.gameScreenElements[UIELEMENT_HISTORY].commandId = COMMAND_NONE;

    ui.gameScreenElements[UIELEMENT_BOARD].x = 20;
    ui.gameScreenElements[UIELEMENT_BOARD].y = 1;
    ui.gameScreenElements[UIELEMENT_BOARD].width = -1;
    ui.gameScreenElements[UIELEMENT_BOARD].height = -1;
    ui.gameScreenElements[UIELEMENT_BOARD].commandId = COMMAND_POSITION;

    return ui;
}

void updateUI(
    UI* const pUI,
    int const boardSize
)
{
    assert( pUI && "Pointer is invalid" );

    pUI->gameScreenElements[UIELEMENT_BOARD].width = ( boardSize * 4 ) + 1;
    pUI->gameScreenElements[UIELEMENT_BOARD].height = ( boardSize * 4 ) + 1;
}

#endif
