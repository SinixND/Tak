#ifndef IG20260327175731
#define IG20260327175731

#include "App.h"

//* Context

/// Setup backend context
void setupBackend( void );

/// Close backend context
void closeBackend( void );

//* Timing

/// Important: Calls `void updateFrame(App* const pApp)`
void loopBackend( App* const pApp );

//* Input

/// Normalize user input from backend
void pollInput( InputBuffer* const pInput );

//* Render

/**
 * @brief: Render static, non-changing content
 *
 * Renders:
 * - Board w/ edges and square corners
 * - Board headers (file/rank display)
 * - Info pane (static content)
 * - Separator line
 */
void renderStatic( App* const app );

/// Render dynamic application content
void renderDynamic( App* const pApp );

#endif
