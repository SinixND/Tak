#ifndef IG20260320143947
#define IG20260320143947

//* Positions
static int const POSITION_RESERVES_WHITE_REGULAR[] = { 5, 45 };
static int const POSITION_RESERVES_WHITE_CAPSTONe[] = { 5, 48 };
static int const POSITION_SCORE_WHITE[] = { 5, 50 };
static int const POSITION_RESERVES_BLACK_REGULAR[] = { 6, 45 };
static int const POSITION_RESERVES_BLACK_CAPSTONe[] = { 6, 48 };
static int const POSITION_SCORE_BLACK[] = { 6, 50 };
static int const POSITION_TURN[] = { 7, 43 };
static int const POSITION_PLAYER_SYMBOL[] = { 7, 50 };
static int const POSITION_INPUT_TYPE[] = { 8, 44 };
static int const POSITION_INPUT_OPTIONS[] = { 9, 43 };
static int const POSITION_INPUT_DISPLAY[] = { 10, 40 };
static int const POSITION_HISTORY_TOP_LEFT[] = { 12, 38 };

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
