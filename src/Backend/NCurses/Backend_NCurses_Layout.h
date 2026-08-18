#ifndef IG20260419211535
#define IG20260419211535

#define LAYOUT_PANE_HEIGHT 13
#define LAYOUT_BOARD_SQUARE_SIZE 4

static int const BOARD_LABELS_X_LEFT = 19;
static int const BOARD_LABELS_Y_TOP = 0;
static int const BOARD_POS_X = 20;
static int const BOARD_POS_Y = 1;
static int const HISTORY_RENDER_COUNT = 2;
static int const PLAYER_COLOR_WHITE = 1;
static int const PLAYER_COLOR_BLACK = 2;
static int const LAYOUT_COLOR = 3;
static int const CPAIR_FGB_BGW = 1;
static int const CPAIR_FGW_BGB = 2;
static int const CPAIR_FGW = 3;
static int const CPAIR_FGB = 4;
static int const CPAIR_LAYOUT = 5;

/// Positions (y, x)
static int const POSITION_STACK_BUFFER[] = { 2, 3 };
static int const POSITION_WHITE_RESERVES_REGULAR[] = { 6, 8 };
static int const POSITION_WHITE_RESERVES_CAPSTONE[] = { 6, 11 };
static int const POSITION_WHITE_RESERVES_SCORE[] = { 6, 14 };
// static int const POSITION_WHITE_SCORE[] = { 6, 13 };
static int const POSITION_BLACK_RESERVES_REGULAR[] = { 7, 8 };
static int const POSITION_BLACK_RESERVES_CAPSTONE[] = { 7, 11 };
static int const POSITION_BLACK_RESERVES_SCORE[] = { 7, 14 };
// static int const POSITION_SCORE_BLACK[] = { 7, 13 };
static int const POSITION_ACTIVE_PLAYER[] = { 8, 8 };
static int const POSITION_PLAYER_SYMBOL[] = { 8, 15 };
static int const POSITION_INPUT_TYPE[] = { 9, 7 };
static int const POSITION_INPUT_OPTIONS[] = { 10, 7 };
static int const POSITION_INPUT_CURRENT[] = { 11, 2 };
static int const POSITION_HISTORY_TOP_LEFT[] = { 13, 0 };

static char* const LAYOUT_INFO_PANE[LAYOUT_PANE_HEIGHT] = {
    "StackBuffer <<  >>",
    "  +   +     <<  >>",
    "",
    "            |<  \\/",
    "            |<  /\\",
    "  +   +  R|C Score",
    "White:    |  ",
    "Black:    |  ",
    "Active:       [ ]",
    "Input:",
    "Opts :",
    ">",
    "History:",
};

static char* const LAYOUT_LABELS_FILE = {
    "   A   B   C   D   E   F   G   H",
};

static char* const LAYOUT_LABELS_RANK[] = {
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
static char* const LAYOUT_BOARD_SQUARE[LAYOUT_BOARD_SQUARE_SIZE + 1] = {
    "+   +",
    "     ",
    "     ",
    "     ",
    "+   +",
};

#endif
