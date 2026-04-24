#ifndef IG20260327175731
#define IG20260327175731

#include "App.h"

/// Context

/// Setup backend context
void setupBackend( void );

/// Close backend context
void closeBackend( void );

/// Timing

/// Important: Calls `void updateFrame(App* const pApp)`
void loopBackend( App* const pApp );

/// Input

/// Normalize user input from backend
void pollInput( InputBuffer* const pInput );

/// Render

/**
 * @brief: Render static, non-changing content
 *
 * Renders:
 * - Info pane (static content)
 * - Board
 */
void renderStatic( App* const app );

/**
 * @brief: Render dynamic, changing content
 *
 * Renders:
 * - Info pane content
 * - Board content
 */
void renderDynamic( App* const pApp );

#endif
