#ifndef IG20260320143947
#define IG20260320143947

//* Positions
static int const POSITION_WHITE_RESERVES_REGULAR[] = { 5, 44 };
static int const POSITION_WHITE_RESERVES_CAPSTONE[] = { 5, 47 };
static int const POSITION_SCORE_WHITE[] = { 5, 49 };
static int const POSITION_BLACK_RESERVES_REGULAR[] = { 6, 44 };
static int const POSITION_BLACK_RESERVES_CAPSTONE[] = { 6, 47 };
static int const POSITION_SCORE_BLACK[] = { 6, 49 };
static int const POSITION_TURN[] = { 7, 42 };
static int const POSITION_PLAYER_SYMBOL[] = { 7, 49 };
static int const POSITION_INPUT_TYPE[] = { 8, 43 };
static int const POSITION_INPUT_OPTIONS[] = { 9, 42 };
static int const POSITION_INPUT_DISPLAY[] = { 10, 39 };
static int const POSITION_HISTORY_TOP_LEFT[] = { 12, 37 };

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
    "      N",
    "    W + E",
    "      S",
    "       R |C|Sc",
    "White:   | |",
    "Black:   | |",
    "Turn:      [ ]",
    "Input:",
    "Opts:",
    ">",
    "History:",
};
#endif
