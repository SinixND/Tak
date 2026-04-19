#include "BackendInterface.h"

#include "Layout.h"

#ifdef BACKEND_NCURSES
#include <ncurses.h>

void renderInfoPane( void );

void renderFileLabels(
    int const fileLabelsOffsetX,
    int const boardSize
);

void renderRankLabels(
    int const ruleLabelsOffsetY,
    int const boardSize
);

void renderBoard(
    int const fileLabelsOffsetX,
    int const ruleLabelsOffsetY,
    int const boardSize
);

void renderBoardEdges(
    int const fileLabelsOffsetX,
    int const ruleLabelsOffsetY,
    int const boardSize
);

void renderStatic( App* const pApp )
{
    renderInfoPane();

    int const boardSize = pApp->game.board.size;
    int const fileLabelsOffsetX = 1;
    int const ruleLabelsOffsetY = 1;

    renderFileLabels(
        fileLabelsOffsetX,
        boardSize
    );

    renderRankLabels(
        ruleLabelsOffsetY,
        boardSize
    );

    renderBoard(
        fileLabelsOffsetX,
        ruleLabelsOffsetY,
        boardSize
    );

    renderBoardEdges(
        fileLabelsOffsetX,
        ruleLabelsOffsetY,
        boardSize
    );
}

void renderInfoPane( void )
{
    for ( int paneIdx = 0; paneIdx < ( LAYOUT_PANE_HEIGHT ); ++paneIdx )
    {
        mvprintw(
            paneIdx,
            0,
            "%s",
            LAYOUT_INFO_PANE[paneIdx]
        );
    }
}

void renderFileLabels(
    int const fileLabelsOffsetX,
    int const boardSize
)
{
    //* Top
    mvprintw(
        0,
        BOARD_OFFSET_X + fileLabelsOffsetX,
        "%.*s", // Partly render file labels
        fileLabelsOffsetX + 1 + ( boardSize * 4 ),
        LAYOUT_LABELS_FILE
    );

    //* Bottom
    mvprintw(
        2 + ( boardSize * LAYOUT_BOARD_SQUARE_SIZE ),
        BOARD_OFFSET_X + fileLabelsOffsetX,
        "%.*s",
        fileLabelsOffsetX + 1 + ( boardSize * 4 ),
        LAYOUT_LABELS_FILE
    );
}

void renderRankLabels(
    int const ruleLabelsOffsetY,
    int const boardSize
)
{
    int const offsetIntoRankLabelsLayout
        = ( ( BOARD_SIZE_MAX - boardSize )
            * LAYOUT_BOARD_SQUARE_SIZE );

    //* Left
    for ( int y = 0; y < ( boardSize * LAYOUT_BOARD_SQUARE_SIZE ); ++y )
    {
        mvprintw(
            ruleLabelsOffsetY + y,
            BOARD_OFFSET_X,
            "%s",
            LAYOUT_LABELS_RANK[offsetIntoRankLabelsLayout + y]
        );
    }

    //* Right
    for ( int y = 0; y < ( boardSize * LAYOUT_BOARD_SQUARE_SIZE ); ++y )
    {
        mvprintw(
            ruleLabelsOffsetY + y,
            BOARD_OFFSET_X + 2 + ( boardSize * LAYOUT_BOARD_SQUARE_SIZE ),
            "%s",
            LAYOUT_LABELS_RANK[offsetIntoRankLabelsLayout + y]
        );
    }
}

void renderBoard(
    int const fileLabelsOffsetX,
    int const ruleLabelsOffsetY,
    int const boardSize
)
{
    int const gridOffsetX = BOARD_OFFSET_X + fileLabelsOffsetX;
    int const gridOffsetY = ruleLabelsOffsetY;

    for ( int y = 0; y < boardSize; ++y )
    {
        for ( int x = 0; x < boardSize; ++x )
        {
            for ( int gridSquareIdx = 0; gridSquareIdx < ( LAYOUT_BOARD_SQUARE_SIZE + 1 ); ++gridSquareIdx )
            {
                mvprintw(
                    gridOffsetY + ( y * ( LAYOUT_BOARD_SQUARE_SIZE ) ) + gridSquareIdx,
                    gridOffsetX + ( x * ( LAYOUT_BOARD_SQUARE_SIZE ) ),
                    "%s",
                    LAYOUT_BOARD_SQUARE[gridSquareIdx]
                );
            }
        }
    }
}

void renderBoardEdges(
    int const fileLabelsOffsetX,
    int const ruleLabelsOffsetY,
    int const boardSize
)
{
    //* Render top board edge
    for ( int x = 0; x < ( boardSize * LAYOUT_BOARD_SQUARE_SIZE ) - 1; ++x )
    {
        mvaddch(
            ruleLabelsOffsetY,
            BOARD_OFFSET_X + fileLabelsOffsetX + 1 + x,
            '-'
        );
    }

    //* Render left board edge
    for ( int y = 0; y < ( boardSize * LAYOUT_BOARD_SQUARE_SIZE ) - 1; ++y )
    {
        mvaddch(
            ruleLabelsOffsetY + 1 + y,
            BOARD_OFFSET_X + fileLabelsOffsetX,
            '|'
        );
    }

    //* Render right board edge
    for ( int y = 0; y < ( boardSize * LAYOUT_BOARD_SQUARE_SIZE ) - 1; ++y )
    {
        mvaddch(
            ruleLabelsOffsetY + 1 + y,
            BOARD_OFFSET_X + fileLabelsOffsetX + ( boardSize * LAYOUT_BOARD_SQUARE_SIZE ),
            '|'
        );
    }

    //* Render bottom board edge
    for ( int x = 0; x < ( boardSize * LAYOUT_BOARD_SQUARE_SIZE ) - 1; ++x )
    {
        mvaddch(
            ruleLabelsOffsetY + ( boardSize * LAYOUT_BOARD_SQUARE_SIZE ),
            BOARD_OFFSET_X + fileLabelsOffsetX + 1 + x,
            '-'
        );
    }
}

void renderDynamic( App* const pApp )
{
    mvprintw(
        1,
        0,
        "%c",
        INPUT_CHARS[pApp->inputBuffer.keyboard]
    );
}

#endif
