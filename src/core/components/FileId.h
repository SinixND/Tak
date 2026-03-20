#ifndef IG20260301185229
#define IG20260301185229

/// Column
typedef enum
{
    FILE_NONE = -1,
    FILE_A = 0,
    FILE_B = 1,
    FILE_C = 2,
    FILE_D = 3,
    FILE_E = 4,
    FILE_F = 5,
    FILE_G = 6,
    FILE_H = 7,
} FileId;

static char const FILE_CHARS[] = {
    ' ',
    'a',
    'b',
    'c',
    'd',
    'e',
    'f',
    'g',
    'h',
};
#endif
