#include "Prompts.h"

#include "CommandId.h"
#include "CommandStateId.h"
#include "InputId.h"
#include "Mappings.h"
#include <assert.h>

Prompts newPrompts( Mappings const* const pMappings )
{
    assert(
        pMappings
        && "Pointer is nullptr"
    );

    return (Prompts){
        .pInputs = {
            [COMMAND_STATE_NONE] = " ---      ",
            [COMMAND_STATE_DEFAULT] = "Pos|Type ",
            [COMMAND_STATE_GET_POSITION] = "Col / Row",
            [COMMAND_STATE_GET_DIRECTION] = "Direction ",
            [COMMAND_STATE_GET_FIRST_DROP_AMOUNT] = "Amount    ",
            [COMMAND_STATE_GET_DROP_AMOUNT] = "Amount    ",
        },
        .options = {
            // clang-format off
            [COMMAND_STATE_NONE] = {
                ' ', '-', '-', '-', ' ', ' ', ' ', ' ', ' ', ' ', '\0'
            },
            [COMMAND_STATE_DEFAULT]  = {
                INPUT_ID_CHARS[pMappings->inputs[CONTEXT_INPUT_DEFAULT][COMMAND_A]],
                '-',
                INPUT_ID_CHARS[pMappings->inputs[CONTEXT_INPUT_DEFAULT][COMMAND_8]],
                ',',
                ' ',
                INPUT_ID_CHARS[pMappings->inputs[CONTEXT_STONE_TYPE][COMMAND_FLAT]],
                '|', 
                INPUT_ID_CHARS[pMappings->inputs[CONTEXT_STONE_TYPE][COMMAND_STANDING]],
                '|', 
                INPUT_ID_CHARS[pMappings->inputs[CONTEXT_STONE_TYPE][COMMAND_CAPSTONE]],
                '\0'
            },
            [COMMAND_STATE_GET_POSITION]  = {
                INPUT_ID_CHARS[pMappings->inputs[CONTEXT_POSITION][COMMAND_A]],
                '-',
                INPUT_ID_CHARS[pMappings->inputs[CONTEXT_POSITION][COMMAND_H]],
                ',', ' ', 
                INPUT_ID_CHARS[pMappings->inputs[CONTEXT_POSITION][COMMAND_1]],
                '-', 
                INPUT_ID_CHARS[pMappings->inputs[CONTEXT_POSITION][COMMAND_8]],
                '.', ' ', '\0'
            },
            [COMMAND_STATE_GET_DIRECTION]  = {
                INPUT_ID_CHARS[pMappings->inputs[CONTEXT_DIRECTION][COMMAND_UP]],
                ',', ' ',
                INPUT_ID_CHARS[pMappings->inputs[CONTEXT_DIRECTION][COMMAND_DOWN]],
                ',', ' ',
                INPUT_ID_CHARS[pMappings->inputs[CONTEXT_DIRECTION][COMMAND_LEFT]],
                ',', ' ',
                INPUT_ID_CHARS[pMappings->inputs[CONTEXT_DIRECTION][COMMAND_RIGHT]],
                '\0'
            },
            [COMMAND_STATE_GET_FIRST_DROP_AMOUNT]  = {
                INPUT_ID_CHARS[pMappings->inputs[CONTEXT_AMOUNT][COMMAND_0]],
                ',', ' ',
                INPUT_ID_CHARS[pMappings->inputs[CONTEXT_AMOUNT][COMMAND_1]],
                ',', ' ', '.', '.', '.', ' ', '\0'
            },
            [COMMAND_STATE_GET_DROP_AMOUNT] = {
                INPUT_ID_CHARS[pMappings->inputs[CONTEXT_AMOUNT][COMMAND_1]],
                ',', ' ',
                INPUT_ID_CHARS[pMappings->inputs[CONTEXT_AMOUNT][COMMAND_2]],
                ' ', '.', '.', ',', ' ',
                INPUT_ID_CHARS[pMappings->inputs[CONTEXT_AMOUNT][COMMAND_ALL]],
                '\0'
            },
            // clang-format on
        },
    };
}
