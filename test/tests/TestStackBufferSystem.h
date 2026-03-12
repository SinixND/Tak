#ifndef IG20260104182516
#define IG20260104182516

#include "GameConstants.h"
#include "PlayerId.h"
#include "StackBuffer.h"
#include "StackBufferSystem.h"
#include "StoneType.h"
#include <unity.h>

void testNewStackBuffer( void )
{
    StackBuffer buffer = newStackBuffer();

    TEST_ASSERT_EQUAL_INT( STONE_TYPE_NONE, buffer.stoneType );
    TEST_ASSERT_EQUAL_INT( 0, buffer.stoneCount );
    TEST_ASSERT_EQUAL_INT( PLAYER_NONE, buffer.stoneIds[0] );
    TEST_ASSERT_EQUAL_INT( PLAYER_NONE, buffer.stoneIds[BOARD_WIDTH_MAX - 1] );
}

void testResetStackBuffer( void )
{
    StackBuffer buffer = newStackBuffer();

    resetBuffer(
        &buffer,
        STONE_TYPE_STANDING
    );

    TEST_ASSERT_EQUAL_INT( STONE_TYPE_STANDING, buffer.stoneType );
}

void testAppendToBuffer( void )
{
    StackBuffer buffer = newStackBuffer();

    resetBuffer(
        &buffer,
        STONE_TYPE_STANDING
    );

    appendToBuffer(
        &buffer,
        PLAYER_BLACK
    );

    TEST_ASSERT_EQUAL_INT( STONE_TYPE_STANDING, buffer.stoneType );
    TEST_ASSERT_EQUAL_INT( 1, buffer.stoneCount );
    TEST_ASSERT_EQUAL_INT( PLAYER_BLACK, buffer.stoneIds[0] );
}

void testDropFromBuffer( void )
{
    StackBuffer buffer = newStackBuffer();

    buffer.stoneType = STONE_TYPE_STANDING;
    buffer.stoneIds[0] = PLAYER_WHITE;
    buffer.stoneIds[1] = PLAYER_BLACK;
    buffer.stoneCount = 2;

    dropFromBuffer( &buffer );

    TEST_ASSERT_EQUAL_INT( 1, buffer.stoneCount );

    dropFromBuffer( &buffer );

    TEST_ASSERT_EQUAL_INT( 0, buffer.stoneCount );
}

#endif
