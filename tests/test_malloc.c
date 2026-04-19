//
// Unit tests for malloc implementation
//

#include "test.h"
#include "../src/malloc/malloc.h"

TEST_SUITE(malloc_basic)
{
    // Test: malloc with non-zero size should not return NULL
    void *ptr = malloc(100);
    TEST_ASSERT(ptr != NULL, "malloc(100) should not return NULL");

    // Clean up
    munmap(ptr, 100);
}

TEST_SUITE(malloc_zero_size)
{
    // Test: malloc with zero size should return NULL
    void *ptr = malloc(0);
    TEST_ASSERT(ptr == NULL, "malloc(0) should return NULL");
}

TEST_SUITE(malloc_small_allocation)
{
    // Test: malloc small allocation
    void *ptr = malloc(10);
    TEST_ASSERT(ptr != NULL, "malloc(10) should not return NULL");
    TEST_ASSERT((uintptr_t)ptr % 4096 == 0, "malloc should return page-aligned memory");

    munmap(ptr, 10);
}

TEST_SUITE(malloc_large_allocation)
{
    // Test: malloc large allocation
    size_t size = 1024 * 1024; // 1 MB
    void *ptr = malloc(size);
    TEST_ASSERT(ptr != NULL, "malloc(1MB) should not return NULL");

    munmap(ptr, size);
}

TEST_SUITE(malloc_multiple_allocations)
{
    // Test: multiple malloc calls should return different addresses
    void *ptr1 = malloc(100);
    void *ptr2 = malloc(200);
    void *ptr3 = malloc(150);

    TEST_ASSERT(ptr1 != NULL, "First malloc should succeed");
    TEST_ASSERT(ptr2 != NULL, "Second malloc should succeed");
    TEST_ASSERT(ptr3 != NULL, "Third malloc should succeed");
    TEST_ASSERT(ptr1 != ptr2, "Different malloc calls should return different pointers");
    TEST_ASSERT(ptr2 != ptr3, "Different malloc calls should return different pointers");
    TEST_ASSERT(ptr1 != ptr3, "Different malloc calls should return different pointers");

    munmap(ptr1, 100);
    munmap(ptr2, 200);
    munmap(ptr3, 150);
}

TEST_SUITE(malloc_memory_access)
{
    // Test: allocated memory should be readable and writable
    char *ptr = (char *)malloc(100);
    TEST_ASSERT(ptr != NULL, "malloc(100) should succeed");

    // Write to allocated memory
    strcpy(ptr, "Hello, World!");
    ptr[99] = 'Z';

    // Read from allocated memory
    TEST_ASSERT(strcmp(ptr, "Hello, World!") == 0, "Should be able to read string from allocated memory");
    TEST_ASSERT(ptr[99] == 'Z', "Should be able to write to end of allocated memory");
    TEST_ASSERT(ptr[0] == 'H', "Should be able to read individual bytes from allocated memory");

    munmap(ptr, 100);
}

TEST_SUITE(malloc_sequential_allocations)
{
    // Test: sequential allocations should each get their own memory
    int *ptr1 = (int *)malloc(sizeof(int) * 10);
    int *ptr2 = (int *)malloc(sizeof(int) * 10);

    TEST_ASSERT(ptr1 != NULL && ptr2 != NULL, "Sequential allocations should succeed");

    // Write different values
    ptr1[0] = 42;
    ptr2[0] = 100;

    // Verify independence
    TEST_ASSERT(ptr1[0] == 42, "ptr1 should contain its own value");
    TEST_ASSERT(ptr2[0] == 100, "ptr2 should contain its own value");
    TEST_ASSERT(ptr1[0] != ptr2[0], "Allocations should be independent");

    munmap(ptr1, sizeof(int) * 10);
    munmap(ptr2, sizeof(int) * 10);
}

TEST_SUITE(malloc_edge_cases)
{
    // Test: very small allocation
    void *ptr1 = malloc(1);
    TEST_ASSERT(ptr1 != NULL, "malloc(1) should succeed");
    munmap(ptr1, 1);

    // Test: exact page size (typically 4096 on most systems)
    void *ptr2 = malloc(4096);
    TEST_ASSERT(ptr2 != NULL, "malloc(4096) should succeed");
    munmap(ptr2, 4096);

    // Test: large allocation
    void *ptr3 = malloc(10 * 1024 * 1024);
    TEST_ASSERT(ptr3 != NULL, "malloc(10MB) should succeed");
    munmap(ptr3, 10 * 1024 * 1024);
}


