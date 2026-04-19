# FSMs
- One frame covers time from input to input

## FSM: App loop
`-`

## FSM - Multi-frame user input handling
### States:
[1] Request Action
[2] Request StoneType
[3] Request FileX
[4] Request RankY
[5] Request Direction
[6] Request First Drop Count
[7] Request Drop Count


### Flow / Paths:
[1] Request Action (Path 1: `Placment`)
    ---> [2] Request StoneType
    ---> [3] Request FileX
    ---> [4] Request RankY

[1] Request Action (Path 2: `Move`)
    ---> [3] Request FileX
    ---> [4] Request RankY

[4] Request RankY (Path 1: `Action: Placement`)
    ---> [1] Request Action

[4] Request RankY (Path 2: `Action: Move`)
    ---> [5] Request Direction
    ---> [6] Request First Drop Count
    ---> [7] Request Drop Count

