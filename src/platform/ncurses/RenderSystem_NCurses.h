#ifndef IG20260317224649
#define IG20260317224649

#include "App.h"

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

/**
 * @brief: Backend dependent rendering system
 */
void renderDynamic( App* const app );

/// Render info pane content
void renderInfoPaneContent( App* const app );

/// Render stack buffer
void renderStackBuffer( App* const app );

/// Render content of a square
void renderSquare( App* const app );

#endif
