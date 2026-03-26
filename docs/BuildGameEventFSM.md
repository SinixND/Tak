# FSMs
## FSM: App loop

### States:
Maybe more states will emerge

[1] Build event / Idle / Wait for input
[2] Handle/apply event

### Flow / Paths:
[1] Build event
    ---> [2] Handle event

[2] Handle event
    ---> [1] Build event

## FSM: Build game event (user input)
The get states should validate input and add them to the built event

### States:
[1] Request Action
[2] Request StoneType
[3] Request FileX
[4] Request RankY
[5] Request Direction
[6] Request First Drop Count
[7] Request Drop Count
[8] Event complete


### Flow / Paths:
[1] Request Action (Path 1: `Placment`)
    ---> [2] Request StoneType
    ---> [3] Request FileX
    ---> [4] Request RankY
    ---> [8] Event complete

[1] Request Action (Path 2: `Lift`)
    ---> [3] Request FileX
    ---> [4] Request RankY
    ---> [8] Event complete
    ---> [1] Request Action

[1] Request Action (Path 3: `Drop`)
    ---> [5] Request Direction
    ---> [6] Request First Drop Count

[6] Request First Drop Count (Path 1: `Event not complete`)
    ---> [7] Request Drop Count

[6] Request First Drop Count (Path 2: `Event complete`)
    ---> [8] Event complete
    ---> [1] Request Action

[7] Request Drop Count (Path 1: `Event not complete`)
    ---> [7] Request Drop Count

[7] Request Drop Count (Path 2: `Event complete`)
    ---> [8] Event complete
    ---> [1] Request Action
