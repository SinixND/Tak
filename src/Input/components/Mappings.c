#include "Mappings.h"

#include "CommandId.h"
#include "ContextId.h"
#include "InputId.h"
#include "UIElement.h"

Mappings newMappings( void )
{
    Mappings mappings = {
        .inputs = {
            [CONTEXT_INPUT_FIRST] = {
                [COMMAND_FLAT] = INPUT_CAP_F,
                [COMMAND_STANDING] = INPUT_CAP_S,
                [COMMAND_CAPSTONE] = INPUT_CAP_C,
                [COMMAND_A] = INPUT_A,
                [COMMAND_B] = INPUT_B,
                [COMMAND_C] = INPUT_C,
                [COMMAND_D] = INPUT_D,
                [COMMAND_E] = INPUT_E,
                [COMMAND_F] = INPUT_F,
                [COMMAND_G] = INPUT_G,
                [COMMAND_H] = INPUT_H,
                [COMMAND_PLACE] = INPUT_P,
                [COMMAND_MOVE] = INPUT_M,
            },
            [CONTEXT_ACTION_TYPE] = {
                [COMMAND_PLACE] = INPUT_P,
                [COMMAND_MOVE] = INPUT_M,
            },
            [CONTEXT_STONE_TYPE] = {
                [COMMAND_FLAT] = INPUT_CAP_F,
                [COMMAND_STANDING] = INPUT_CAP_S,
                [COMMAND_CAPSTONE] = INPUT_CAP_C,
            },
            [CONTEXT_POSITION] = {
                [COMMAND_A] = INPUT_A,
                [COMMAND_B] = INPUT_B,
                [COMMAND_C] = INPUT_C,
                [COMMAND_D] = INPUT_D,
                [COMMAND_E] = INPUT_E,
                [COMMAND_F] = INPUT_F,
                [COMMAND_G] = INPUT_G,
                [COMMAND_H] = INPUT_H,
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
            [CONTEXT_AMOUNT] = {
                [COMMAND_0] = INPUT_0,
                [COMMAND_1] = INPUT_1,
                [COMMAND_2] = INPUT_2,
                [COMMAND_3] = INPUT_3,
                [COMMAND_4] = INPUT_4,
                [COMMAND_5] = INPUT_5,
                [COMMAND_6] = INPUT_6,
                [COMMAND_7] = INPUT_7,
                [COMMAND_8] = INPUT_8,
                [COMMAND_ALL] = INPUT_A,
            },
            [CONTEXT_SIZE] = {
                [COMMAND_3] = INPUT_3,
                [COMMAND_4] = INPUT_4,
                [COMMAND_5] = INPUT_5,
                [COMMAND_6] = INPUT_6,
                [COMMAND_7] = INPUT_7,
                [COMMAND_8] = INPUT_8,
                [COMMAND_CONFIRM] = INPUT_SPACE,
            },
            [CONTEXT_GLOBAL] = {
                [COMMAND_QUIT] = INPUT_CAP_Q,
                [COMMAND_RESET] = INPUT_CAP_X,
                [COMMAND_UNDO] = INPUT_CAP_U,
                [COMMAND_REDO] = INPUT_CAP_R,
            }
        },
        .uiElements = {
            // TODO: Store positions in Layout
            // clang-format off
            [CONTEXT_GLOBAL] = {
                 (UIElement){
                    .x = 12,
                    .y = 0,
                    .width = 2,
                    .height = 2,
                    .commandId = COMMAND_UNDO
                },
                (UIElement){
                    .x = 16,
                    .y = 0,
                    .width = 2,
                    .height = 2,
                    .commandId = COMMAND_REDO
                },
                (UIElement){
                    .x = 12,
                    .y = 2,
                    .width = 2,
                    .height = 2,
                    .commandId = COMMAND_RESET
                },
                (UIElement){
                    .x = 16,
                    .y = 2,
                    .width = 2,
                    .height = 2,
                    .commandId = COMMAND_QUIT
                },
            },
            // clang-format on
        },
    };

    /// Commands
    for ( int contextId = 0; contextId < CONTEXT_COUNT; ++contextId )
    {
        for ( int commandId = 0; commandId < COMMAND_COUNT; ++commandId )
        {
            InputId const inputId = mappings.inputs[contextId][commandId];
            mappings.commands[contextId][inputId] = commandId;
        }
    }

    return mappings;
}
