//
// Main test runner
//

#include "test.h"
#include "../src/malloc/malloc.h"
#include "../src/free/free.h"
#include "../src/realloc/realloc.h"

// Global test counters
int g_tests_run = 0;
int g_tests_passed = 0;
int g_tests_failed = 0;

// Forward declarations of all test suites
void run_test_suite_malloc_basic(void);
void run_test_suite_malloc_zero_size(void);
void run_test_suite_malloc_small_allocation(void);
void run_test_suite_malloc_large_allocation(void);
void run_test_suite_malloc_multiple_allocations(void);
void run_test_suite_malloc_memory_access(void);
void run_test_suite_malloc_sequential_allocations(void);
void run_test_suite_malloc_edge_cases(void);

void run_test_suite_free_basic(void);
void run_test_suite_free_null_pointer(void);
void run_test_suite_free_multiple_allocations(void);
void run_test_suite_free_sequential_malloc_free(void);
void run_test_suite_free_various_sizes(void);

void run_test_suite_realloc_basic(void);
void run_test_suite_realloc_zero_size(void);
void run_test_suite_realloc_shrink(void);
void run_test_suite_realloc_grow(void);
void run_test_suite_realloc_multiple_times(void);

// Print test summary
void print_test_summary(void)
{
    printf("\n");
    printf("========================================\n");
    printf("Test Summary\n");
    printf("========================================\n");
    printf("Total Tests Run:   %d\n", g_tests_run);
    printf("Tests Passed:      %d\n", g_tests_passed);
    printf("Tests Failed:      %d\n", g_tests_failed);
    printf("========================================\n");

    if (g_tests_failed == 0) {
        printf("✓ All tests passed!\n");
    } else {
        printf("✗ Some tests failed!\n");
    }
    printf("========================================\n\n");
}

int main(void)
{
    printf("\n");
    printf("╔════════════════════════════════════════╗\n");
    printf("║    Malloc Implementation Test Suite    ║\n");
    printf("╚════════════════════════════════════════╝\n");

    // Run malloc tests
    RUN_SUITE(malloc_basic);
    RUN_SUITE(malloc_zero_size);
    RUN_SUITE(malloc_small_allocation);
    RUN_SUITE(malloc_large_allocation);
    RUN_SUITE(malloc_multiple_allocations);
    RUN_SUITE(malloc_memory_access);
    RUN_SUITE(malloc_sequential_allocations);
    RUN_SUITE(malloc_edge_cases);

    // Run free tests
    RUN_SUITE(free_basic);
    RUN_SUITE(free_null_pointer);
    RUN_SUITE(free_multiple_allocations);
    RUN_SUITE(free_sequential_malloc_free);
    RUN_SUITE(free_various_sizes);

    // Run realloc tests
    RUN_SUITE(realloc_basic);
    RUN_SUITE(realloc_zero_size);
    RUN_SUITE(realloc_shrink);
    RUN_SUITE(realloc_grow);
    RUN_SUITE(realloc_multiple_times);

    // Print summary
    print_test_summary();

    // Return exit code based on test results
    return g_tests_failed == 0 ? 0 : 1;
}

