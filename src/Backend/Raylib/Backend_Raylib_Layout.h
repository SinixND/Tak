#ifndef IG20260615173249
#define IG20260615173249

#include <raylib.h>

enum
{
    WINDOW_WIDTH = 400,
    WINDOW_HEIGHT = 200,
    WINDOW_WIDTH_MIN = 200,
    WINDOW_HEIGHT_MIN = 100,
    FPS_TARGET = 30,
};

static Color const COLOR_BG = BLACK;
static Color const COLOR_FG = RAYWHITE;

enum
{
    LAYOUT_PANE_HEIGHT = 13,
    LAYOUT_PANE_WIDTH = 17,
    BOARD_OFFSET_X = LAYOUT_PANE_WIDTH + 2,
    LAYOUT_BOARD_SQUARE_SIZE = 4,
    HISTORY_RENDER_COUNT = 2,
    PLAYER_COLOR_WHITE = 1,
    PLAYER_COLOR_BLACK = 2,
    LAYOUT_COLOR = 3,
    CPAIR_WHITE_1 = 1,
    CPAIR_BLACK_1 = 2,
    CPAIR_WHITE_2 = 3,
    CPAIR_BLACK_2 = 4,
    CPAIR_LAYOUT = 5,
};

/// Positions (y, x)
static Vector2 const POSITION_STACK_BUFFER[] = { { 2, 3 } };
static Vector2 const POSITION_WHITE_RESERVES_REGULAR[] = { { 6, 8 } };
static Vector2 const POSITION_WHITE_RESERVES_CAPSTONE[] = { { 6, 11 } };
static Vector2 const POSITION_WHITE_RESERVES_SCORE[] = { { 6, 14 } };
// static Vector2 const POSITION_WHITE_SCORE[] = {{ 6, 13 }};
static Vector2 const POSITION_BLACK_RESERVES_REGULAR[] = { { 7, 8 } };
static Vector2 const POSITION_BLACK_RESERVES_CAPSTONE[] = { { 7, 11 } };
static Vector2 const POSITION_BLACK_RESERVES_SCORE[] = { { 7, 14 } };
// static Vector2 const POSITION_SCORE_BLACK[] = {{ 7, 13 }};
static Vector2 const POSITION_ACTIVE_PLAYER[] = { { 8, 8 } };
static Vector2 const POSITION_PLAYER_SYMBOL[] = { { 8, 15 } };
static Vector2 const POSITION_INPUT_TYPE[] = { { 9, 7 } };
static Vector2 const POSITION_INPUT_OPTIONS[] = { { 10, 7 } };
static Vector2 const POSITION_INPUT_CURRENT[] = { { 11, 2 } };
static Vector2 const POSITION_HISTORY_TOP_LEFT[] = { { 13, 0 } };

static char* const LAYOUT_INFO_PANE[] = {
    "StackBuffer",
    "  +   +",
    "",
    "",
    "",
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
