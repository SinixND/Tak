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
    }
}
