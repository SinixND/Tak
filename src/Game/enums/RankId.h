#ifndef IG20260301185429
#define IG20260301185429

/// Row
typedef enum RankId
{
    RANK_NONE = -1,
    RANK_1 = 0,
    RANK_2 = 1,
    RANK_3 = 2,
    RANK_4 = 3,
    RANK_5 = 4,
    RANK_6 = 5,
    RANK_7 = 6,
    RANK_8 = 7,
} RankId;

static char const RANK_CHARS[] = {
   [RANK_1] = '1',
   [RANK_2] = '2',
   [RANK_3] = '3',
   [RANK_4] = '4',
   [RANK_5] = '5',
   [RANK_6] = '6',
   [RANK_7] = '6',
   [RANK_8] = '8',
};

#endif
