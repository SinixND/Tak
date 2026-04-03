```c
struct App
+  shouldClose
+ struct(Game) game
|   + struct(Reserves) reserves
|   |   + (int)[players] reservesRegular
|   |   + (int)[players] reservesCapstone
|   |   + (int) stonesInPlay
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
+ struct(History) history
|   + (int) lastActionIdx
|   + (int) redoCount
|   + struct(HistoryRecord)[historySize]
|       + enum(ActionType) actionType
|       + enum(PlayerId) playerId
|       + enum(StoneType) stoneType
|       + (int) squareIdx 
|       + (int) topStoneIndex
|       + (int) stoneCount
|       + (bool) flattened
|       
```
