#ifndef IG20260317162853
#define IG20260317162853

typedef enum InputId
{
    INPUT_NONE,

    INPUT_0,
    INPUT_1,
    INPUT_2,
    INPUT_3,
    INPUT_4,
    INPUT_5,
    INPUT_6,
    INPUT_7,
    INPUT_8,

    INPUT_A,
    INPUT_B,
    INPUT_C,
    INPUT_D,
    INPUT_E,
    INPUT_F,
    INPUT_G,
    INPUT_H,

    INPUT_L,
    INPUT_M,
    INPUT_P,
    INPUT_R,
    INPUT_T,
    INPUT_U,

    INPUT_SPACE,

    INPUT_CAP_C,
    INPUT_CAP_F,
    INPUT_CAP_S,
    INPUT_CAP_Q,
    INPUT_CAP_R,
    INPUT_CAP_U,
    INPUT_CAP_X,

    INPUT_MOUSE,

    INPUT_COUNT
} InputId;

static char const INPUT_ID_CHARS[] = {
    [INPUT_NONE] = ' ',
    [INPUT_0] = '0',
    [INPUT_1] = '1',
    [INPUT_2] = '2',
    [INPUT_3] = '3',
    [INPUT_4] = '4',
    [INPUT_5] = '5',
    [INPUT_6] = '6',
    [INPUT_7] = '7',
    [INPUT_8] = '8',
    [INPUT_A] = 'a',
    [INPUT_B] = 'b',
    [INPUT_C] = 'c',
    [INPUT_D] = 'd',
    [INPUT_E] = 'e',
    [INPUT_F] = 'f',
    [INPUT_G] = 'g',
    [INPUT_H] = 'h',
    [INPUT_L] = 'l',
    [INPUT_M] = 'm',
    [INPUT_P] = 'p',
    [INPUT_R] = 'r',
    [INPUT_U] = 'u',
    [INPUT_SPACE] = '_',
    [INPUT_CAP_C] = 'C',
    [INPUT_CAP_F] = 'F',
    [INPUT_CAP_S] = 'S',
    [INPUT_CAP_Q] = 'Q',
    [INPUT_CAP_R] = 'R',
    [INPUT_CAP_U] = 'U',
    [INPUT_CAP_X] = 'X',
};

#endif
