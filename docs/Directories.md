+ src/
   + app/ # [layer] Application
   + platform/ # [layer] Platform / Backend
   + input/ # [layer] Input
   + render/ # [layer] Rendering
   + engine/ # [layer] Engine
   |   + turn/ # [module] TurnState
   |   + event/ # [module] GameEvent
   |   + history/ # [module] History
   |   + flow/ # [module] EventFlow
   |   + rules/ # [module] Rules
   + game/ # [layer] Game / Core
       + board/ # [module] Board
       + reserves/ # [module] Reserves
       + stack_buffer/ # [module] StackBuffer
