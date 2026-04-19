#ifndef IG20260320143947
#define IG20260320143947

enum
{
    LAYOUT_PANE_HEIGHT = 13,
    LAYOUT_PANE_WIDTH = 17,
    BOARD_OFFSET = LAYOUT_PANE_WIDTH + 2,
    LAYOUT_BOARD_SQUARE_SIZE = 4,
    MAX_COMMAND_LENGTH = 11,
};

//* Positions
static int const POSITION_STACK_BUFFER[] = { 2, 3 };
static int const POSITION_WHITE_RESERVES_REGULAR[] = { 6, 8 };
static int const POSITION_WHITE_RESERVES_CAPSTONE[] = { 6, 11 };
// static int const POSITION_WHITE_SCORE[] = { 6, 13 };
static int const POSITION_BLACK_RESERVES_REGULAR[] = { 7, 8 };
static int const POSITION_BLACK_RESERVES_CAPSTONE[] = { 7, 11 };
// static int const POSITION_SCORE_BLACK[] = { 7, 13 };
static int const POSITION_TURN[] = { 8, 7 };
static int const POSITION_PLAYER_SYMBOL[] = { 8, 14 };
static int const POSITION_INPUT_TYPE[] = { 9, 7 };
static int const POSITION_INPUT_OPTIONS[] = { 10, 7 };
static int const POSITION_INPUT_CURRENT[] = { 11, 3 };
static int const POSITION_HISTORY_TOP_LEFT[] = { 13, 1 };

static char* const LAYOUT_INFO_PANE[] = {
    "StackBuffer   N  ",
    "  +   +     W + E",
    "              S  ",
    "",
    "",
    "  +   +  R|C",
    "White:    |",
    "Black:    |",
    "Turn :       [ ]",
    "Input:",
    "Opts :",
    ">",
    "History:",
};

static char* const LAYOUT_BOARD_HEADER_RANK = {
    "   A   B   C   D   E   F   G   H",
};

static char* const LAYOUT_BOARD_HEADER_FILE[] = {
    " ",
    " ",
    " ",
    "8",
    " ",
    " ",
    " ",
    "7",
    " ",
    " ",
    " ",
    "6",
    " ",
    " ",
    " ",
    "5",
    " ",
    " ",
    " ",
    "4",
    " ",
    " ",
    " ",
    "3",
    " ",
    " ",
    " ",
    "2",
    " ",
    " ",
    " ",
    "1",
    " ",
    " ",
    " ",
};
static char* const LAYOUT_BOARD_SQUARE[] = {
    "+   +",
    "     ",
    "     ",
    "     ",
    "+   +",
};

#endif
