#include "InputSystem_NCurses.h"

#include "InputId.h"
#include <ncurses.h>

InputId pollInput( void )
{
    switch ( getch() )
    {
        default:
        {
            //* Do nothing
            return INPUT_NONE;
        }

        case 'a':
        {
            return INPUT_A;
        }

        case 'b':
        {
            return INPUT_B;
        }

        case 'c':
        {
            return INPUT_C;
        }

        case 'd':
        {
            return INPUT_D;
        }

        case 'e':
        {
            return INPUT_E;
        }

        case 'f':
        {
            return INPUT_F;
        }

        case 'g':
        {
            return INPUT_G;
        }

        case 'h':
        {
            return INPUT_H;
        }

        case 'l':
        {
            return INPUT_L;
        }

        case 'm':
        {
            return INPUT_M;
        }

        case 'n':
        {
            return INPUT_N;
        }

        case 'p':
        {
            return INPUT_P;
        }

        case 'Q':
        {
            return INPUT_Q;
        }

        case 'r':
        {
            return INPUT_R;
        }

        case 's':
        {
            return INPUT_S;
        }

        case 'u':
        {
            return INPUT_U;
        }

        case 'w':
        {
            return INPUT_W;
        }

        case '0':
        {
            return INPUT_0;
        }

        case '1':
        {
            return INPUT_1;
        }

        case '2':
        {
            return INPUT_2;
        }

        case '3':
        {
            return INPUT_3;
        }

        case '4':
        {
            return INPUT_4;
        }

        case '5':
        {
            return INPUT_5;
        }

        case '6':
        {
            return INPUT_6;
        }

        case '7':
        {
            return INPUT_7;
        }

        case '8':
        {
            return INPUT_8;
        }
    }
}
