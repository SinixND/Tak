#include "Prompts.h"

#include "CommandId.h"
#include "CommandStateId.h"
#include "InputId.h"
#include "Keymap.h"

Prompts newPrompts( Keymap const* const pKeymap )
{
    return (Prompts){
        .inputs = {
            [STATE_NONE] = " ---      ",
            [STATE_GET_ACTION_TYPE] = "Action    ",
            [STATE_GET_STONE_TYPE] = "Stone Type",
            [STATE_GET_FILE_X] = "File / Col",
            [STATE_GET_RANK_Y] = "Rank / Row",
            [STATE_GET_DIRECTION] = "Direction ",
            [STATE_GET_FIRST_DROP_AMOUNT] = "Amount    ",
            [STATE_GET_DROP_AMOUNT] = "Amount    ",
        },
        .options = {
            // clang-format off
            [STATE_NONE] = {
                ' ', '-', '-', '-', ' ', ' ', ' ', ' ', ' ', ' ', '\0'
            },
            [STATE_GET_ACTION_TYPE]  = {
                INPUT_ID_CHARS[pKeymap->inputs[CONTEXT_ACTION_TYPE][COMMAND_PLACE]],
                ',', ' ',
                INPUT_ID_CHARS[pKeymap->inputs[CONTEXT_ACTION_TYPE][COMMAND_MOVE]],
                ' ', ' ', ' ', ' ', ' ', ' ', '\0'
            },
            [STATE_GET_STONE_TYPE]  = {
                INPUT_ID_CHARS[pKeymap->inputs[CONTEXT_STONE_TYPE][COMMAND_FLAT]],
                ',', ' ',
                INPUT_ID_CHARS[pKeymap->inputs[CONTEXT_STONE_TYPE][COMMAND_STANDING]],
                ',', ' ',
                INPUT_ID_CHARS[pKeymap->inputs[CONTEXT_STONE_TYPE][COMMAND_CAPSTONE]],
                ' ', ' ', ' ', '\0'
            },
            [STATE_GET_FILE_X]  = {
                INPUT_ID_CHARS[pKeymap->inputs[CONTEXT_POSITION][COMMAND_A]],
                ',', ' ',
                INPUT_ID_CHARS[pKeymap->inputs[CONTEXT_POSITION][COMMAND_B]],
                ',', ' ', '.', '.', '.', ' ', '\0'
            },
            [STATE_GET_RANK_Y]  = {
                INPUT_ID_CHARS[pKeymap->inputs[CONTEXT_POSITION][COMMAND_1]],
                ',', ' ',
                INPUT_ID_CHARS[pKeymap->inputs[CONTEXT_POSITION][COMMAND_2]],
                ',', ' ', '.', '.', '.', ' ', '\0'
            },
            [STATE_GET_DIRECTION]  = {
                INPUT_ID_CHARS[pKeymap->inputs[CONTEXT_DIRECTION][COMMAND_UP]],
                ',', ' ',
                INPUT_ID_CHARS[pKeymap->inputs[CONTEXT_DIRECTION][COMMAND_DOWN]],
                ',', ' ',
                INPUT_ID_CHARS[pKeymap->inputs[CONTEXT_DIRECTION][COMMAND_LEFT]],
                ',', ' ',
                INPUT_ID_CHARS[pKeymap->inputs[CONTEXT_DIRECTION][COMMAND_RIGHT]],
                '\0'
            },
            [STATE_GET_FIRST_DROP_AMOUNT]  = {
                INPUT_ID_CHARS[pKeymap->inputs[CONTEXT_AMOUNT][COMMAND_0]],
                ',', ' ',
                INPUT_ID_CHARS[pKeymap->inputs[CONTEXT_AMOUNT][COMMAND_1]],
                ',', ' ', '.', '.', '.', ' ', '\0'
            },
            [STATE_GET_DROP_AMOUNT] = {
                INPUT_ID_CHARS[pKeymap->inputs[CONTEXT_AMOUNT][COMMAND_1]],
                ',', ' ',
                INPUT_ID_CHARS[pKeymap->inputs[CONTEXT_AMOUNT][COMMAND_2]],
                ' ', '.', '.', ',', ' ',
                INPUT_ID_CHARS[pKeymap->inputs[CONTEXT_AMOUNT][COMMAND_ALL]],
                '\0'
            },
            // clang-format on
        },
    };
}
