# Data Flow
InputBuffer
-> Command
-> Event
-> Game
-> History

# Logic Flou
Input
-> buildCommand()
    parseInput() ? continue
    validateInput() ? continue
    updateCommand()
-> handleCommand()
    buildEvent()
    (validateEvent())
    executeEvent()
-> Render
