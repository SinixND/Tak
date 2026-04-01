# Data Flow

InputBuffer
    ↓
TurnState
    ↓
GameEvent
    ↓
Rules Validation
    ↓
Event Application (Engine)
    ↓
Game State Update
    ↓
History Update
    ↓
Rendering

---
# Application [layer]
`orchestrates main loop`
+ connects input → engine → game → rendering

---

# Game / Core [layer]
`pure game state and rules`
+ no UI, no orchestration

## Board [module]
`2D grid of stacks`
+ [data] stacks

## Reserves [module]
`remaining stones per player`
+ [data] counts per player

## StackBuffer [module]
`temporarily holds lifted stones`
+ [data] lifted stack

## Rules [module]
`validates game events`
+ [system] validate_event
+ [system] check_win

---

# Engine [layer]
`transforms input into state changes`
+ owns game progression

## InputBuffer [module]
`frame-based raw input`
+ [data] key states

## TurnState [module]
`multi-frame user intent`
+ [data] cursor, selection, partial action

## GameEvent [module]
`atomic player action`
+ [data] event type + parameters

## History [module]
`event log`
+ [data] list of GameEvents
+ [system] undo / redo

## EventFlow [module]
`drives game progression`
+ [system] build_event (TurnState → GameEvent)
+ [system] validate (via Rules)
+ [system] apply_event (to Game)
+ [system] update_history

---

# Rendering [layer]
`visualizes current state`
+ reads Game + TurnState

## Render [module]
`draws current frame`
+ [system] draw_board
+ [system] draw_cursor
+ [system] highlight

---

# Platform / Backend [layer]
`low-level IO (ncurses)`
+ platform abstraction

## IO [module]
`input/output primitives`
+ [system] poll_input
+ [system] draw_char / refresh
---
