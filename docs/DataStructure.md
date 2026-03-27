```c
struct App
+  shouldClose
+ struct(Game) game
|   + struct(Players) players
|   |   + (int)[players] reservesRegular
|   |   + (int)[players] reservesCapstone
|   |   + (int) stonesInPlay
|   |   
|   + struct(History) history
|   |   + (int) lastActionIdx
|   |   + (int) redoCount
|   |   + struct(PlayerAction)[historySize]
|   |       + enum(ActionType) actionType
|   |       + enum(PlayerId) playerId
|   |       + enum(StoneType) stoneType
|   |       + (int) squareIdx 
|   |       + (int) topStoneIndex
|   |       + (int) stoneCount
|   |       + (bool) flattened
|   |       
|   + struct(StackBuffer) stackBuffer
|   |   + enum(PlayerId)[maxBoardWidth] stoneType
|   |   + enum(StoneType) stoneType
|   |   + (int) stoneCount
|   |   + 
|   + struct(Board) board
|       + enum(PlayerId)[maxStones] stoneIds
|       + enum(StoneType)[maxSquareCount] types
|       + (int)[maxSquareCount] stoneCounts
|       + (int) stackCapacity
|       + (int) width
| 
+ 
```