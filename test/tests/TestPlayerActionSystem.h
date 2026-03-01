#ifndef IG20260104182446
#define IG20260104182446

#include "DirectionId.h"
#include "FileId.h"
#include "PlayerActionSystem.h"
#include "PlayerTurn.h"
#include "RankId.h"
#include "StoneType.h"
#include <unity.h>

void testNewPlayerActionPlace( void )
{
    PlayerAction action = newPlayerActionPlace(
        STONE_TYPE_FLAT,
        FILE_A,
        RANK_1
    );

    TEST_ASSERT_EQUAL_INT( 0, action.count );
    TEST_ASSERT_EQUAL_INT( STONE_TYPE_FLAT, action.stoneType );
    TEST_ASSERT_EQUAL_INT( FILE_A, action.file );
    TEST_ASSERT_EQUAL_INT( RANK_1, action.rank );
    TEST_ASSERT_EQUAL_INT( DIR_UP, action.direction );
    TEST_ASSERT_EQUAL_INT( 0, action.flattend );
    TEST_ASSERT_EQUAL_INT( 0, action.drops[0] );
    TEST_ASSERT_EQUAL_INT( 0, action.drops[7] );
}

// void testNewPlayerActionMove( void )
// {
//     PlayerAction action = newPlayerActionMove(
//         2,
//         STONE_TYPE_FLAT,
//         FILE_H,
//         RANK_8,
//         DIR_RIGHT,
//         1,
//         (int[8]){
//             1,
//             0,
//             0,
//             0,
//             0,
//             0,
//             0,
//             0
//         }
//     );
//
//     TEST_ASSERT_EQUAL_INT( 2, action.count );
//     TEST_ASSERT_EQUAL_INT( STONE_TYPE_FLAT, action.stoneType );
//     TEST_ASSERT_EQUAL_INT( FILE_H, action.file );
//     TEST_ASSERT_EQUAL_INT( RANK_8, action.rank );
//     TEST_ASSERT_EQUAL_INT( DIR_RIGHT, action.direction );
//     TEST_ASSERT_EQUAL_INT( 1, action.flattend );
//     TEST_ASSERT_EQUAL_INT( 1, action.drops[0] );
//     TEST_ASSERT_EQUAL_INT( 0, action.drops[7] );
// }

#endif

