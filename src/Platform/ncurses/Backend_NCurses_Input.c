#include "BackendInterface.h"

#include "InputBuffer.h"
#include <assert.h>

#ifdef BACKEND_NCURSES
#include <ncurses.h>

void pollInput( InputBuffer* const pInput )
{
    assert(
        pInput
        && "Pointer is nullptr"
    );

    switch ( getch() )
    {
        case 'a':
        {
            pInput->keyboard = INPUT_A;
            return;
        }

        case 'b':
        {
            pInput->keyboard = INPUT_B;
            return;
        }

        case 'c':
        {
            pInput->keyboard = INPUT_C;
            return;
        }

        case 'd':
        {
            pInput->keyboard = INPUT_D;
            return;
        }

        case 'e':
        {
            pInput->keyboard = INPUT_E;
            return;
        }

        case 'f':
        {
            pInput->keyboard = INPUT_F;
            return;
        }

        case 'g':
        {
            pInput->keyboard = INPUT_G;
            return;
        }

        case 'h':
        {
            pInput->keyboard = INPUT_H;
            return;
        }

        case 'l':
        {
            pInput->keyboard = INPUT_L;
            return;
        }

        case 'm':
        {
            pInput->keyboard = INPUT_M;
            return;
        }

        case 'n':
        {
            pInput->keyboard = INPUT_N;
            return;
        }

        case 'p':
        {
            pInput->keyboard = INPUT_P;
            return;
        }

        case 'Q':
        {
            pInput->keyboard = INPUT_Q;
            return;
        }

        case 'r':
        {
            pInput->keyboard = INPUT_R;
            return;
        }

        case 's':
        {
            pInput->keyboard = INPUT_S;
            return;
        }

        case 'u':
        {
            pInput->keyboard = INPUT_U;
            return;
        }

        case 'w':
        {
            pInput->keyboard = INPUT_W;
            return;
        }

        case '0':
        {
            pInput->keyboard = INPUT_0;
            return;
        }

        case '1':
        {
            pInput->keyboard = INPUT_1;
            return;
        }

        case '2':
        {
            pInput->keyboard = INPUT_2;
            return;
        }

        case '3':
        {
            pInput->keyboard = INPUT_3;
            return;
        }

        case '4':
        {
            pInput->keyboard = INPUT_4;
            return;
        }

        case '5':
        {
            pInput->keyboard = INPUT_5;
            return;
        }

        case '6':
        {
            pInput->keyboard = INPUT_6;
            return;
        }

        case '7':
        {
            pInput->keyboard = INPUT_7;
            return;
        }

        case '8':
        {
            pInput->keyboard = INPUT_8;
            return;
        }

        default:
        {
            pInput->keyboard = INPUT_NONE;
            return;
        }
    }
}

#endif
