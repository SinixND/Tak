#ifndef IG20260705032717
#define IG20260705032717

#ifdef BACKEND_RAYLIB
#include <raylib.h>
#endif

/**
 * @brief Data used by backend to calculate the UI
 *
 * Note: Only required by raylib, not ncurses
 */
typedef struct UIData
{
    /// Required for ncurses because no empty structs allowed
    int fontSize;
#ifdef BACKEND_RAYLIB
    Font font;
    int fontWidth;
    int spacing;
#endif
} UIData;

UIData newUIData( void );

#endif
