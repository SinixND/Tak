#ifndef IG20260501155114
#define IG20260501155114

typedef enum CommandId
{
    COMMAND_NONE,
    /// Player action
    COMMAND_PLACE,
    COMMAND_MOVE,
    /// Stone type
    COMMAND_FLAT,
    COMMAND_STANDING,
    COMMAND_CAPSTONE,
    /// File
    COMMAND_A,
    COMMAND_B,
    COMMAND_C,
    COMMAND_D,
    COMMAND_E,
    COMMAND_F,
    COMMAND_G,
    COMMAND_H,
    /// Rank and count
    COMMAND_0,
    COMMAND_1,
    COMMAND_2,
    COMMAND_3,
    COMMAND_4,
    COMMAND_5,
    COMMAND_6,
    COMMAND_7,
    COMMAND_8,
    /// Direction
    COMMAND_UP,
    COMMAND_DOWN,
    COMMAND_LEFT,
    COMMAND_RIGHT,
    /// Global inputs
    COMMAND_QUIT,
    COMMAND_RESET,
    COMMAND_UNDO,
    COMMAND_REDO,
    /// Enum size
    COMMAND_COUNT,
} CommandId;

#endif

