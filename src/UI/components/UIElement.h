#ifndef IG20260728124832
#define IG20260728124832

#include "CommandId.h"
#include <stdbool.h>

/// @brief: Links position with command
typedef struct UIElement
{
    float x;
    float y;
    float width;
    float height;
    CommandId commandId;
    char const* text;
} UIElement;

#endif

