#ifndef IG20260705032717
#define IG20260705032717

#ifdef BACKEND_RAYLIB
#include <raylib.h>
#endif

typedef struct UIData
{
    int fontSize;
#ifdef BACKEND_RAYLIB
    Font font;
    int fontWidth;
    int spacing;
#endif
} UIData;

UIData newUIData( void );

#endif
