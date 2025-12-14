#include "PlacementSystem.test.c"
#include <check.h>
#include <stdlib.h>

//* Group test cases in suite (required)
Suite* testSuiteNameCreate( void )
{
    Suite* suite;
    TCase* core;

    suite = suite_create( "SuiteName" );
    core = tcase_create( "TCaseName" );

    //* Add tests to Tcase
    tcase_add_test( core, PlaceStone );

    //* Add Tcase to Suite
    suite_add_tcase( suite, core );

    //* Return the whole test suite
    return suite;
}

int main( void )
{
    int failed;
    Suite* suite;
    SRunner* runner;

    suite = testSuiteNameCreate();
    runner = srunner_create( suite );

    srunner_run_all( runner, CK_NORMAL );
    failed = srunner_ntests_failed( runner );
    srunner_free( runner );

    return ( failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE );
}
