#ifndef IG20260410152134
#define IG20260410152134

#include "App.h"

/**
 * @brief: Build command from input
 *
 * - Parse input
 * - Validate
 */
void buildCommand( App* const pApp );

#endif
/*
/// Choose what game event to prepare
void handleStateGetAction( Command* const pCommand, InputBuffer const* const pInputBuffer );

/// Get stone type
void handleStateGetStoneType( Command* const pCommand, InputBuffer const* const pInputBuffer );

/// Get column of target square
void handleStateGetFileX( Command* const pCommand, InputBuffer const* const pInputBuffer );

/// Get row of target square
void handleStateGetRankY( Command* const pCommand, InputBuffer const* const pInputBuffer );

/// Get direction to move stack
void handleStateGetDirection( Command* const pCommand, InputBuffer const* const pInputBuffer );

/// Get drop count (can be 0 on initial square)
void handleStateGetFirstDropAmount( Command* const pCommand, InputBuffer const* const pInputBuffer );

/// Get drop count
void handleStateGetDropAmount( Command* const pCommand, InputBuffer const* const pInputBuffer );
   */
