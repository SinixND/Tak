#include "BackendInterface.h"

#ifdef BACKEND_NCURSES

#include "AppSystem.h"
#include "InputBuffer.h"

#include <ncurses.h>

void setupBackend( void )
{
    initscr(); // Start ncurses mode
    cbreak();  // Disable line buffering, pass keys to program immediately
    // halfdelay( 1 ); // Non-blocking: Waits n/10ths of a second for input
    noecho();      // Don’t print typed characters automatically
    curs_set( 0 ); // Hide cursor

    keypad( stdscr, TRUE ); // Enable arrow keys and function keys
}

void closeBackend( void )
{
    endwin(); // Restore terminal
}

void loopBackend( App* const pApp )
{
    while ( !pApp->shouldClose )
    {
        updateFrame( pApp );
    }
}

void pollInput( InputBuffer* const pInput )
{
    switch ( getch() )
    {
        default:
        {
            pInput->keyboard = INPUT_NONE;
            return;
        }

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
    }
}

#endif

