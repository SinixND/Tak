#ifndef IG20260419211535
#define IG20260419211535

#define LAYOUT_BOARD_SQUARE_SIZE 4

static int const PLAYER_COLOR_WHITE = 1;
static int const PLAYER_COLOR_BLACK = 2;
static int const LAYOUT_COLOR = 3;
static int const HIGHLIGHT_COLOR = 4;

static int const CPAIR_FGB_BGW = 1;
static int const CPAIR_FGW_BGB = 2;
static int const CPAIR_FGW = 3;
static int const CPAIR_FGB = 4;
static int const CPAIR_LAYOUT = 5;
static int const CPAIR_HIGHLIGHT = 6;

/// Positions (y, x)
static int const POSITION_BOARD[]
    = { 0, 19 };

static int const POSITION_STACK_BUFFER[]
    = { 2, 3 };
static int const POSITION_WHITE_RESERVES_REGULAR[]
    = { 6, 8 };
static int const POSITION_WHITE_RESERVES_CAPSTONE[]
    = { 6, 11 };
static int const POSITION_WHITE_SCORE[]
    = { 6, 14 };
static int const POSITION_BLACK_RESERVES_REGULAR[]
    = { 7, 8 };
static int const POSITION_BLACK_RESERVES_CAPSTONE[]
    = { 7, 11 };
static int const POSITION_BLACK_SCORE[]
    = { 7, 14 };
static int const POSITION_ACTIVE_PLAYER[]
    = { 8, 8 };
static int const POSITION_PLAYER_SYMBOL[]
    = { 8, 15 };
static int const POSITION_INPUT_CURRENT[]
    = { 9, 2 };
static int const POSITION_HISTORY[]
    = { 11, 0 };

static char const LAYOUT_INFO_PANE[]
    = "StackBuffer <<  >>\n"
      "  +   +     <<  >>\n"
      "\n"
      "            |<  \\/\n"
      "            |<  /\\\n"
      "  +   +  R|C Score\n"
      "White:    |  \n"
      "Black:    |  \n"
      "Active:       [ ]\n"
      ">\n"
      "History:\n";

static char const LAYOUT_LABELS_FILE[]
    = "   A   B   C   D   E   F   G   H";

static char const LAYOUT_LABELS_RANK[]
    = "   8   7   6   5   4   3   2   1";

static char const LAYOUT_BOARD_SQUARE[]
    = "+   +\n"
      "     \n"
      "     \n"
      "     \n"
      "+   +\n";

#endif
