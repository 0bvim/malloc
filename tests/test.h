//
// Simple testing framework for malloc implementation
//

#ifndef MALLOC_TEST_H
#define MALLOC_TEST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <assert.h>

// Test counters
extern int g_tests_run;
extern int g_tests_passed;
extern int g_tests_failed;

// Macros for testing
#define TEST_ASSERT(condition, message) \
    do { \
        g_tests_run++; \
        if (!(condition)) { \
            printf("  ✗ FAIL: %s\n", message); \
            g_tests_failed++; \
        } else { \
            printf("  ✓ PASS: %s\n", message); \
            g_tests_passed++; \
        } \
    } while (0)

#define TEST_SUITE(name) \
    void test_##name(void); \
    void run_test_suite_##name(void) { \
        printf("\n=== Testing %s ===\n", #name); \
        test_##name(); \
    } \
    void test_##name(void)

#define RUN_SUITE(name) run_test_suite_##name()

// Helper function to print test summary
void print_test_summary(void);

#endif // MALLOC_TEST_H

