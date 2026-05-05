#ifndef IG20260301185229
#define IG20260301185229

/// Column
typedef enum FileId
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
    [FILE_A] = 'a',
    [FILE_B] = 'b',
    [FILE_C] = 'c',
    [FILE_D] = 'd',
    [FILE_E] = 'e',
    [FILE_F] = 'f',
    [FILE_G] = 'g',
    [FILE_H] = 'h',
};

#endif
