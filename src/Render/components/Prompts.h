#ifndef IG20260323100845
#define IG20260323100845

#include "CommandStateId.h"
#include "Prompt.h"

static Prompt const PROMPTS[] = {
    // clang-format off
    [STATE_GET_ACTION_TYPE] 
        = { 
            .input = "Action    ", 
            .options = "P, M      " 
        },
    [STATE_GET_STONE_TYPE] 
        = {
            .input = "Stone Type",
            .options = "F, S, C   ",
        },
    [STATE_GET_FILE_X] 
        = {
            .input = "File / Col",
            .options = "A, B, ... ",
        },
    [STATE_GET_RANK_Y] 
        = {
            .input = "Rank / Row",
            .options = "1, 2, ... ",
        },
    [STATE_GET_DIRECTION] 
        = {
            .input = "Direction ",
            .options = "N, E, S, W",
        },
    [STATE_GET_FIRST_DROP_AMOUNT] 
        = {
            .input = "Amount    ",
            .options = "0, 1, ... ",
        },
    [STATE_GET_DROP_AMOUNT] 
        = {
            .input = "Amount    ",
            .options = "1, 2, ... ",
        },
    // clang-format on
};

#endif
