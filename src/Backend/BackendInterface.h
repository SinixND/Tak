#ifndef IG20260327175731
#define IG20260327175731

#include "App.h"

/// Context

/// Setup backend context
void setupBackend( void );

/// Close backend context
void closeBackend( void );

/// Timing

/// Delay execution for n milliseconds
void wait( int const ms );

/// Input

/// Normalize user input from backend
void pollInput( InputBuffer* const pInput );

/// Render

/// Render app state
void render( App const* const pApp );

/**
 * @brief: Render static, non-changing content
 *
 * Renders:
 * - Info pane (static content)
 * - Board
 */
// void renderStatic( App const* const app );

/**
 * @brief: Render dynamic, changing content
 *
 * Renders:
 * - Info pane content
 * - Board content
 */
// void renderDynamic( App const* const pApp );

/// Render starting screen (choose board size)
// void renderStartScreen( void );

/// Render command for finished game
// void renderCommandGameEnd( App const* const pApp );

#endif
