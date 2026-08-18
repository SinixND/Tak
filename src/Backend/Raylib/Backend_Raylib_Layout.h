#ifndef IG20260615173249
#define IG20260615173249

#include <raylib.h>

#define LAYOUT_STACK_BUFFER_SIZE 8
#define LAYOUT_PLAYER_INFO_SIZE 8
#define LAYOUT_BOARD_SQUARE_SIZE 4

static int const WINDOW_WIDTH = 40;
static int const WINDOW_HEIGHT = 20;
static int const WINDOW_WIDTH_MIN = 20;
static int const WINDOW_HEIGHT_MIN = 10;
static int const FPS_TARGET = 3;

static Color const COLOR_BG = BLACK;
static Color const COLOR_FG = RAYWHITE;

static int const BOARD_LABELS_X_LEFT = 0;
static int const BOARD_LABELS_Y_TOP = 9;
static int const BOARD_POS_X = 1;
static int const BOARD_POS_Y = 10;
static int const PLAYER_COLOR_WHITE = 1;
static int const PLAYER_COLOR_BLACK = 2;
static int const LAYOUT_COLOR = 3;
static int const CPAIR_WHITE_1 = 1;
static int const CPAIR_BLACK_1 = 2;
static int const CPAIR_WHITE_2 = 3;
static int const CPAIR_BLACK_2 = 4;
static int const CPAIR_LAYOUT = 5;

/// Positions (y, x)
static int const POSITION_STACK_BUFFER[] = { 30, 0 };
static int const POSITION_PLAYER_INFO[] = { 0, 0 };
static int const POSITION_WHITE_RESERVES_REGULAR[] = { 6, 8 };
static int const POSITION_WHITE_RESERVES_CAPSTONE[] = { 6, 11 };
static int const POSITION_WHITE_RESERVES_SCORE[] = { 6, 14 };
static int const POSITION_BLACK_RESERVES_REGULAR[] = { 7, 8 };
static int const POSITION_BLACK_RESERVES_CAPSTONE[] = { 7, 11 };
static int const POSITION_BLACK_RESERVES_SCORE[] = { 7, 14 };
static int const POSITION_ACTIVE_PLAYER[] = { 8, 8 };
static int const POSITION_PLAYER_SYMBOL[] = { 8, 15 };
static int const POSITION_INPUT_TYPE[] = { 9, 7 };
static int const POSITION_INPUT_OPTIONS[] = { 10, 7 };
static int const POSITION_INPUT_CURRENT[] = { 11, 2 };
static int const POSITION_HISTORY_TOP_LEFT[] = { 13, 0 };

static char* const LAYOUT_STACK_BUFFER[LAYOUT_STACK_BUFFER_SIZE] = {
    "+-----------+",
    "|StackBuffer|",
    "|   +   +   |",
    "|           |",
    "|           |",
    "|           |",
    "|   +   +   |",
    "+-----------+",
};

static char* const LAYOUT_PLAYER_INFO[LAYOUT_PLAYER_INFO_SIZE] = {
    "+------------------------+",
    "|          WHITE | BLACK |",
    "|SCORE:          |       |",
    "|REGULAR:        |       |",
    "|CAPSTONE:       |       |",
    "|                        |",
    "|ACTIVE:                 |",
    "+------------------------+",
};

static char* const LAYOUT_LABELS_FILE = {
    "  A   B   C   D   E   F   G   H",
};

static char* const LAYOUT_LABELS_RANK[] = {
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
