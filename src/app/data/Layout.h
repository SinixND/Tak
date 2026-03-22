#ifndef IG20260320143947
#define IG20260320143947

//* Positions
static int const POSITION_WHITE_RESERVES_REGULAR[] = { 6, 25 };
static int const POSITION_WHITE_RESERVES_CAPSTONE[] = { 6, 28 };
static int const POSITION_WHITE_SCORE[] = { 6, 30 };
static int const POSITION_BLACK_RESERVES_REGULAR[] = { 7, 25 };
static int const POSITION_BLACK_RESERVES_CAPSTONE[] = { 7, 28 };
static int const POSITION_SCORE_BLACK[] = { 7, 30 };
static int const POSITION_TURN[] = { 8, 25 };
static int const POSITION_PLAYER_SYMBOL[] = { 8, 31 };
static int const POSITION_INPUT_TYPE[] = { 9, 25 };
static int const POSITION_INPUT_OPTIONS[] = { 10, 25 };
static int const POSITION_INPUT_CURRENT[] = { 11, 21 };
static int const POSITION_HISTORY_TOP_LEFT[] = { 13, 19 };

enum
{
    MAX_COMMAND_LENGTH = 11,
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

static char* const LAYOUT_INFO_PANE[] = {
    "StackBuffer      ",
    "  +   +       N  ",
    "            W + E",
    "              S  ",
    "                 ",
    "  +   +   R|C",
    "White:   |",
    "Black:   |",
    "Turn :      [ ]",
    "Input:",
    "Opts :",
    ">",
    "History:",
};
#endif
