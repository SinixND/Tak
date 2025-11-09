#include <ncurses.h>
#include <stdio.h>

int main( void )
{
    printf( "Hello world!" );

    initscr();
    printw( "Hello ncurses" );
    refresh();
    getch();
    endwin();

    return 0;
}
