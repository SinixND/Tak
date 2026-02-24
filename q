[1mdiff --git a/src/systems/PlayersSystem.c b/src/systems/PlayersSystem.c[m
[1mindex c778996..bb17128 100644[m
[1m--- a/src/systems/PlayersSystem.c[m
[1m+++ b/src/systems/PlayersSystem.c[m
[36m@@ -7,7 +7,7 @@[m
 [m
 Players newPlayers( int const boardWidth )[m
 {[m
[31m-    assert( ( boardWidth >= (int)BOARD_WIDTH_MIN ) && "Board width value too small" );[m
[32m+[m[32m    assert( ( boardWidth >= BOARD_WIDTH_MIN ) && "Board width value too small" );[m
     assert( ( boardWidth <= (int)BOARD_WIDTH_MAX ) && "Board width value too big" );[m
 [m
     Players players = { 0 };[m
[1mdiff --git a/test/tests/TestGameSystem.h b/test/tests/TestGameSystem.h[m
[1mindex 53674f9..ca55333 100644[m
[1m--- a/test/tests/TestGameSystem.h[m
[1m+++ b/test/tests/TestGameSystem.h[m
[36m@@ -38,12 +38,12 @@[m [mvoid testNewGame( void )[m
 [m
     TEST_ASSERT_EQUAL_INT([m
         0,[m
[31m-        game0.board.heights[1][m
[32m+[m[32m        game0.board.stacks[1].height[m
     );[m
 [m
     TEST_ASSERT_EQUAL_INT([m
         0,[m
[31m-        game0.board.stacks[1][0][m
[32m+[m[32m        game0.board.stacks[1].affiliations[0][m
     );[m
 [m
     //* EXECUTE[m
[36m@@ -77,12 +77,12 @@[m [mvoid testNewGame( void )[m
 [m
     TEST_ASSERT_EQUAL_INT([m
         0,[m
[31m-        game3.board.heights[1][m
[32m+[m[32m        game3.board.stacks[1].height[m
     );[m
 [m
     TEST_ASSERT_EQUAL_INT([m
         0,[m
[31m-        game3.board.stacks[1][0][m
[32m+[m[32m        game3.board.stacks[1].affiliations[0][m
     );[m
 }[m
 [m
[1mdiff --git a/test/tests/TestPlacementSystem.h b/test/tests/TestPlacementSystem.h[m
[1mindex 5ff1671..ff73de8 100644[m
[1m--- a/test/tests/TestPlacementSystem.h[m
[1m+++ b/test/tests/TestPlacementSystem.h[m
[36m@@ -27,12 +27,12 @@[m [mvoid testPlaceStoneOnBoard( void )[m
 [m
     TEST_ASSERT_EQUAL_INT([m
         1,[m
[31m-        game.board.heights[0][m
[32m+[m[32m        game.board.stacks[0].height[m
     );[m
 [m
     TEST_ASSERT_EQUAL_INT([m
         1,[m
[31m-        game.board.stacks[0][0][m
[32m+[m[32m        game.board.stacks[0].affiliations[0][m
     );[m
 [m
     TEST_ASSERT_EQUAL_INT([m
[36m@@ -57,12 +57,12 @@[m [mvoid testPlaceStoneOnBoard( void )[m
 [m
     TEST_ASSERT_EQUAL_INT([m
         2,[m
[31m-        game.board.heights[0][m
[32m+[m[32m        game.board.stacks[0].height[m
     );[m
 [m
     TEST_ASSERT_EQUAL_INT([m
         2,[m
[31m-        game.board.stacks[0][1][m
[32m+[m[32m        game.board.stacks[0].affiliations[1][m
     );[m
 [m
     TEST_ASSERT_EQUAL_INT([m
[36m@@ -87,12 +87,12 @@[m [mvoid testPlaceStoneOnBoard( void )[m
 [m
     TEST_ASSERT_EQUAL_INT([m
         3,[m
[31m-        game.board.heights[0][m
[32m+[m[32m        game.board.stacks[0].height[m
     );[m
 [m
     TEST_ASSERT_EQUAL_INT([m
         1,[m
[31m-        game.board.stacks[0][2][m
[32m+[m[32m        game.board.stacks[0].affiliations[2][m
     );[m
 [m
     TEST_ASSERT_EQUAL_INT([m
[1mdiff --git a/test/tests/TestStackSystem.h b/test/tests/TestStackSystem.h[m
[1mindex ad18e59..d87db50 100644[m
[1m--- a/test/tests/TestStackSystem.h[m
[1m+++ b/test/tests/TestStackSystem.h[m
[36m@@ -11,7 +11,6 @@[m [mvoid testNewStack( void )[m
     Stack stack = newStack();[m
 [m
     //* VERIFY[m
[31m-    TEST_ASSERT_EQUAL_INT( (int)NO_STONE, stack.type );[m
     TEST_ASSERT_EQUAL_INT( 0, stack.height );[m
     TEST_ASSERT_EQUAL_INT( 0, stack.affiliations[0] );[m
     TEST_ASSERT_EQUAL_INT( 0, stack.affiliations[44] );[m
