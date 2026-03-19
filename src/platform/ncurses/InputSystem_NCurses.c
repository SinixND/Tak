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

        case '0':
        {
            return INPUT_0;
        }

        case '1':
        {
            return INPUT_0;
        }

        case '2':
        {
            return INPUT_0;
        }

        case '3':
        {
            return INPUT_0;
        }

        case '4':
        {
            return INPUT_0;
        }

        case '5':
        {
            return INPUT_0;
        }

        case '6':
        {
            return INPUT_0;
        }

        case '7':
        {
            return INPUT_0;
        }

        case '8':
        {
            return INPUT_0;
        }

        case 'a':
        case 'A':
        {
            return INPUT_A;
        }

        case 'b':
        case 'B':
        {
            return INPUT_B;
        }

        case 'c':
        case 'C':
        {
            return INPUT_C;
        }

        case 'd':
        case 'D':
        {
            return INPUT_D;
        }

        case 'e':
        case 'E':
        {
            return INPUT_E;
        }

        case 'f':
        case 'F':
        {
            return INPUT_F;
        }

        case 'g':
        case 'G':
        {
            return INPUT_G;
        }

        case 'h':
        case 'H':
        {
            return INPUT_H;
        }

        case 'p':
        case 'P':
        {
            return INPUT_P;
        }

        case 'q':
        case 'Q':
        {
            return INPUT_Q;
        }

        case 's':
        case 'S':
        {
            return INPUT_S;
        }
    }
}
