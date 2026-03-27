#include "BackendInterface.h"

#include "AppSystem.h"
#include "InputBuffer.h"

#ifdef BACKEND_NCURSES
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

void loopBackend( App* const app )
{
    while ( !app->shouldClose )
    {
        updateFrame( app );
    }
}

void pollInput( InputBuffer* const input )
{
    switch ( getch() )
    {
        default:
        {
            input->keyboard = INPUT_NONE;
            return;
        }

        case 'a':
        {
            input->keyboard = INPUT_A;
            return;
        }

        case 'b':
        {
            input->keyboard = INPUT_B;
            return;
        }

        case 'c':
        {
            input->keyboard = INPUT_C;
            return;
        }

        case 'd':
        {
            input->keyboard = INPUT_D;
            return;
        }

        case 'e':
        {
            input->keyboard = INPUT_E;
            return;
        }

        case 'f':
        {
            input->keyboard = INPUT_F;
            return;
        }

        case 'g':
        {
            input->keyboard = INPUT_G;
            return;
        }

        case 'h':
        {
            input->keyboard = INPUT_H;
            return;
        }

        case 'l':
        {
            input->keyboard = INPUT_L;
            return;
        }

        case 'm':
        {
            input->keyboard = INPUT_M;
            return;
        }

        case 'n':
        {
            input->keyboard = INPUT_N;
            return;
        }

        case 'p':
        {
            input->keyboard = INPUT_P;
            return;
        }

        case 'Q':
        {
            input->keyboard = INPUT_Q;
            return;
        }

        case 'r':
        {
            input->keyboard = INPUT_R;
            return;
        }

        case 's':
        {
            input->keyboard = INPUT_S;
            return;
        }

        case 'u':
        {
            input->keyboard = INPUT_U;
            return;
        }

        case 'w':
        {
            input->keyboard = INPUT_W;
            return;
        }

        case '0':
        {
            input->keyboard = INPUT_0;
            return;
        }

        case '1':
        {
            input->keyboard = INPUT_1;
            return;
        }

        case '2':
        {
            input->keyboard = INPUT_2;
            return;
        }

        case '3':
        {
            input->keyboard = INPUT_3;
            return;
        }

        case '4':
        {
            input->keyboard = INPUT_4;
            return;
        }

        case '5':
        {
            input->keyboard = INPUT_5;
            return;
        }

        case '6':
        {
            input->keyboard = INPUT_6;
            return;
        }

        case '7':
        {
            input->keyboard = INPUT_7;
            return;
        }

        case '8':
        {
            input->keyboard = INPUT_8;
            return;
        }
    }
}

#endif

