#include "BackendInterface.h"
#include "Backend_NCurses_Layout.h"

#ifdef BACKEND_NCURSES
#include "InputBuffer.h"
#include "InputId.h"
#include <assert.h>
#include <ncurses.h>

UIPosition getUIPosition(
    float mouseX,
    float mouseY,
    UIData const* const pUIData
)
{
    assert(
        pUIData
        && "Invalid pointer"
    );

    return (UIPosition){
        (int)mouseX,
        (int)mouseY
    };
}

Tile getTile(
    float mouseX,
    float mouseY,
    int boardSize,
    UIData const* const pUIData
)
{
    assert(
        pUIData
        && "Invalid pointer"
    );

    Tile tile = { FILE_NONE, RANK_NONE };

    if (
        ( ( (int)mouseX - ( BOARD_POS_X + 1 ) ) % 4 )
        && ( (int)mouseY - BOARD_POS_Y ) % 4
    )
    {
        tile.fileX
            = ( (int)mouseX - ( BOARD_POS_X + 1 ) ) / 4;

        tile.rankY
            = ( boardSize - 1 ) - ( ( (int)mouseY - 1 ) / 4 );
    }

    return tile;
}

void getInputFromUser( InputBuffer* const pInput )
{
    assert(
        pInput
        && "Pointer is nullptr"
    );

    switch ( getch() )
    {
        case '0':
        {
            pInput->lastInput = INPUT_0;
            return;
        }

        case '1':
        {
            pInput->lastInput = INPUT_1;
            return;
        }

        case '2':
        {
            pInput->lastInput = INPUT_2;
            return;
        }

        case '3':
        {
            pInput->lastInput = INPUT_3;
            return;
        }

        case '4':
        {
            pInput->lastInput = INPUT_4;
            return;
        }

        case '5':
        {
            pInput->lastInput = INPUT_5;
            return;
        }

        case '6':
        {
            pInput->lastInput = INPUT_6;
            return;
        }

        case '7':
        {
            pInput->lastInput = INPUT_7;
            return;
        }

        case '8':
        {
            pInput->lastInput = INPUT_8;
            return;
        }

        case 'a':
        {
            pInput->lastInput = INPUT_A;
            return;
        }

        case 'b':
        {
            pInput->lastInput = INPUT_B;
            return;
        }

        case 'c':
        {
            pInput->lastInput = INPUT_C;
            return;
        }

        case 'd':
        {
            pInput->lastInput = INPUT_D;
            return;
        }

        case 'e':
        {
            pInput->lastInput = INPUT_E;
            return;
        }

        case 'f':
        {
            pInput->lastInput = INPUT_F;
            return;
        }

        case 'g':
        {
            pInput->lastInput = INPUT_G;
            return;
        }

        case 'h':
        {
            pInput->lastInput = INPUT_H;
            return;
        }

        case 'l':
        {
            pInput->lastInput = INPUT_L;
            return;
        }

        case 'm':
        {
            pInput->lastInput = INPUT_M;
            return;
        }

        case 'p':
        {
            pInput->lastInput = INPUT_P;
            return;
        }

        case 'r':
        {
            pInput->lastInput = INPUT_R;
            return;
        }

        case 'u':
        {
            pInput->lastInput = INPUT_U;
            return;
        }

        case ' ':
        {
            pInput->lastInput = INPUT_SPACE;
            return;
        }

        case 'C':
        {
            pInput->lastInput = INPUT_CAP_C;
            return;
        }

        case 'F':
        {
            pInput->lastInput = INPUT_CAP_F;
            return;
        }

        case 'S':
        {
            pInput->lastInput = INPUT_CAP_S;
            return;
        }

        case 'Q':
        {
            pInput->lastInput = INPUT_CAP_Q;
            return;
        }

        case 'R':
        {
            pInput->lastInput = INPUT_CAP_R;
            return;
        }

        case 'U':
        {
            pInput->lastInput = INPUT_CAP_U;
            return;
        }

        case 'X':
        {
            pInput->lastInput = INPUT_CAP_X;
            return;
        }

        case KEY_MOUSE:
        {
            pInput->lastInput = INPUT_MOUSE;

            MEVENT event;
            getmouse( &event );
            pInput->mousePosition[0] = event.x;
            pInput->mousePosition[1] = event.y;

            return;
        }

        default:
        {
            pInput->lastInput = INPUT_NONE;
            return;
        }
    }
}

#endif
