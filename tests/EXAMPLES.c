// Example: How to add custom tests to your malloc test suite

/*
 * This file shows examples of how to extend the test suite
 * Copy patterns from here into test_malloc.c, test_free.c, or test_realloc.c
 */

#include "test.h"
#include "../src/malloc/malloc.h"
#include <sys/mman.h>
#include <string.h>

// ============================================================================
// EXAMPLE 1: Simple basic test
// ============================================================================

TEST_SUITE(example_simple)
{
    // Allocate memory
    int *ptr = (int *)malloc(sizeof(int) * 10);

    // Test that allocation succeeded
    TEST_ASSERT(ptr != NULL, "malloc should return non-NULL for valid size");

    // Clean up
    munmap(ptr, sizeof(int) * 10);
}

// ============================================================================
// EXAMPLE 2: Test with data validation
// ============================================================================

TEST_SUITE(example_data_validation)
{
    // Allocate a buffer
    char *buffer = (char *)malloc(256);
    TEST_ASSERT(buffer != NULL, "malloc should succeed");

    // Write test data
    strcpy(buffer, "Hello, malloc!");

    // Validate data
    TEST_ASSERT(buffer[0] == 'H', "First character should be 'H'");
    TEST_ASSERT(buffer[5] == ',', "Comma should be at position 5");
    TEST_ASSERT(strcmp(buffer, "Hello, malloc!") == 0, "Full string should match");

    // Clean up
    munmap(buffer, 256);
}

// ============================================================================
// EXAMPLE 3: Test with multiple allocations
// ============================================================================

TEST_SUITE(example_multiple_allocs)
{
    // Allocate multiple buffers
    int *arr1 = (int *)malloc(100);
    int *arr2 = (int *)malloc(200);
    char *str = (char *)malloc(50);

    TEST_ASSERT(arr1 != NULL && arr2 != NULL && str != NULL,
                "All allocations should succeed");

    // Verify they're different
    TEST_ASSERT(arr1 != arr2, "Different allocations should have different addresses");
    TEST_ASSERT(arr1 != (int *)str, "Different types should have different addresses");

    // Write to each
    arr1[0] = 42;
    arr2[0] = 100;
    strcpy(str, "test");

    // Verify independence
    TEST_ASSERT(arr1[0] == 42 && arr2[0] == 100, "Allocations should be independent");

    // Clean up
    munmap(arr1, 100);
    munmap(arr2, 200);
    munmap(str, 50);
}

// ============================================================================
// EXAMPLE 4: Test with loops
// ============================================================================

TEST_SUITE(example_repeated_allocs)
{
    // Allocate and deallocate multiple times
    for (int i = 1; i <= 10; i++) {
        void *ptr = malloc(i * 100);
        TEST_ASSERT(ptr != NULL, "Allocation should succeed in loop");
        munmap(ptr, i * 100);
    }
}

// ============================================================================
// EXAMPLE 5: Test array operations
// ============================================================================

TEST_SUITE(example_array_operations)
{
    // Allocate array
    int *array = (int *)malloc(sizeof(int) * 100);
    TEST_ASSERT(array != NULL, "Array allocation should succeed");

    // Write to entire array
    for (int i = 0; i < 100; i++) {
        array[i] = i * 2;
    }

    // Verify entire array
    for (int i = 0; i < 100; i++) {
        TEST_ASSERT(array[i] == i * 2, "Array values should match");
    }

    // Cleanup
    munmap(array, sizeof(int) * 100);
}

// ============================================================================
// EXAMPLE 6: Test for specific error conditions (when free is implemented)
// ============================================================================

/*
TEST_SUITE(example_free_operations)
{
    // Allocate and free
    void *ptr = malloc(100);
    TEST_ASSERT(ptr != NULL, "malloc should succeed");

    free(ptr);
    TEST_ASSERT(1, "free should not crash");

    // After free, the memory should be deallocated
    // (Don't try to use ptr after this point!)
}
*/

// ============================================================================
// EXAMPLE 7: Stress test (allocate many times)
// ============================================================================

TEST_SUITE(example_stress_test)
{
    // Stress test: allocate many blocks
    void *ptrs[100];

    // Allocate 100 blocks
    for (int i = 0; i < 100; i++) {
        ptrs[i] = malloc(64 + i);
        TEST_ASSERT(ptrs[i] != NULL, "Stress allocation should succeed");
    }

    // Verify all are different
    for (int i = 0; i < 100; i++) {
        for (int j = i + 1; j < 100; j++) {
            TEST_ASSERT(ptrs[i] != ptrs[j], "All allocations should be unique");
        }
    }

    // Cleanup
    for (int i = 0; i < 100; i++) {
        munmap(ptrs[i], 64 + i);
    }
}

// ============================================================================
// EXAMPLE 8: Test struct allocation
// ============================================================================

typedef struct {
    int id;
    char name[50];
    double value;
} DataRecord;

TEST_SUITE(example_struct_alloc)
{
    // Allocate a struct
    DataRecord *record = (DataRecord *)malloc(sizeof(DataRecord));
    TEST_ASSERT(record != NULL, "Struct allocation should succeed");

    // Initialize struct
    record->id = 42;
    strcpy(record->name, "Example");
    record->value = 3.14;

    // Verify struct data
    TEST_ASSERT(record->id == 42, "Struct id should match");
    TEST_ASSERT(strcmp(record->name, "Example") == 0, "Struct name should match");
    TEST_ASSERT(record->value > 3.0, "Struct value should be reasonable");

    // Cleanup
    munmap(record, sizeof(DataRecord));
}

// ============================================================================
// EXAMPLE 9: Test size boundaries
// ============================================================================

TEST_SUITE(example_size_boundaries)
{
    // Test allocation at various sizes
    size_t sizes[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024,
                      4096, 8192, 1024*1024};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    for (int i = 0; i < num_sizes; i++) {
        void *ptr = malloc(sizes[i]);
        TEST_ASSERT(ptr != NULL, "Allocation should work at all sizes");
        munmap(ptr, sizes[i]);
    }
}

// ============================================================================
// EXAMPLE 10: Test pointer arithmetic
// ============================================================================

TEST_SUITE(example_pointer_arithmetic)
{
    // Allocate buffer
    char *buffer = (char *)malloc(256);
    TEST_ASSERT(buffer != NULL, "Buffer allocation should succeed");

    // Initialize buffer
    strcpy(buffer, "Start");

    // Use pointer arithmetic
    char *ptr = buffer + 5;  // Move pointer
    strcpy(ptr, "End");

    // Verify result
    TEST_ASSERT(buffer[5] == 'E', "Pointer arithmetic should work");
    TEST_ASSERT(buffer[6] == 'n', "Pointer arithmetic should work");

    // Cleanup
    munmap(buffer, 256);
}

// ============================================================================
// PATTERNS TO FOLLOW
// ============================================================================

/*
 * Test naming convention:
 * - Use lowercase with underscores
 * - Start with what you're testing: malloc_, free_, realloc_
 * - Include what you're testing: basic, edge_case, multiple, etc.
 * - Example: malloc_large_allocation, realloc_grow, free_null
 *
 * Assertion messages should:
 * - Be descriptive and concise
 * - Explain what was expected
 * - Example: "malloc should return NULL for zero size"
 *
 * Test structure:
 * 1. Setup (allocate memory)
 * 2. Test (perform operation)
 * 3. Assert (verify results)
 * 4. Cleanup (free resources)
 *
 * Memory cleanup:
 * - For malloc() tests: use munmap(ptr, size)
 * - For implemented free(): use free(ptr)
 * - Always cleanup to keep tests independent
 */

// ============================================================================
// NEXT STEPS
// ============================================================================

/*
 * To add these examples to your test suite:
 *
 * 1. Choose which test file to add to:
 *    - test_malloc.c for malloc tests
 *    - test_free.c for free tests (when implemented)
 *    - test_realloc.c for realloc tests (when implemented)
 *
 * 2. Copy the TEST_SUITE function from examples above
 *
 * 3. Add to test_runner.c:
 *    - Add forward declaration: void run_test_suite_example_xxx(void);
 *    - Add call in main: RUN_SUITE(example_xxx);
 *
 * 4. Rebuild and test:
 *    - make clean && make test
 *    - or: ./run_tests.sh rebuild
 */

