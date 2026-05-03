#include "Keybinds.h"

#include "CommandId.h"
#include "InputId.h"

Keybinds newKeybinds( void )
{
    Keybinds keybinds = {
        .commands = { [CONTEXT_ACTION_TYPE] = {
                          [COMMAND_PLACE] = INPUT_P,
                          [COMMAND_MOVE] = INPUT_M,
                      },
                      [CONTEXT_STONE_TYPE] = {
                          [COMMAND_FLAT] = INPUT_F,
                          [COMMAND_STANDING] = INPUT_S,
                          [COMMAND_CAPSTONE] = INPUT_C,
                      },
                      [CONTEXT_FILE_X] = {
                          [COMMAND_A] = INPUT_A,
                          [COMMAND_B] = INPUT_B,
                          [COMMAND_C] = INPUT_C,
                          [COMMAND_D] = INPUT_D,
                          [COMMAND_E] = INPUT_E,
                          [COMMAND_F] = INPUT_F,
                          [COMMAND_G] = INPUT_G,
                          [COMMAND_H] = INPUT_H,
                      },
                      [CONTEXT_RANK_Y] = {
                          [COMMAND_0] = INPUT_0,
                          [COMMAND_1] = INPUT_1,
                          [COMMAND_2] = INPUT_2,
                          [COMMAND_3] = INPUT_3,
                          [COMMAND_4] = INPUT_4,
                          [COMMAND_5] = INPUT_5,
                          [COMMAND_6] = INPUT_6,
                          [COMMAND_7] = INPUT_7,
                          [COMMAND_8] = INPUT_8,
                      },
                      [CONTEXT_DIRECTION] = {
                          [COMMAND_UP] = INPUT_U,
                          [COMMAND_DOWN] = INPUT_D,
                          [COMMAND_LEFT] = INPUT_L,
                          [COMMAND_RIGHT] = INPUT_R,
                      },
                      [CONTEXT_GLOBAL] = {
                          [COMMAND_QUIT] = INPUT_CAP_Q,
                          [COMMAND_RESET] = INPUT_CAP_X,
                          [COMMAND_UNDO] = INPUT_CAP_U,
                          [COMMAND_REDO] = INPUT_CAP_R,
                      } };
}

return keybinds;
}
;

#endif
