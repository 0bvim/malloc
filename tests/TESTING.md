# Malloc Implementation Test Suite Documentation

## Overview

A comprehensive test suite for your custom malloc/free/realloc implementation using `mmap`. The test framework is written in pure C with no external dependencies (other than libft which your project already uses).

## Project Structure

```
tests/
├── Makefile              # Build system for tests
├── README.md             # Quick start guide
├── test.h                # Test framework header
├── test_malloc.c         # Tests for malloc()
├── test_free.c           # Tests for free()
├── test_realloc.c        # Tests for realloc()
└── test_runner.c         # Main test runner and entry point
```

## Test Framework

### Core Components

**test.h** provides:
- Test macros (`TEST_ASSERT`, `TEST_SUITE`)
- Test counters for statistics
- Helper functions for reporting

### Key Macros

```c
// Define a test suite
TEST_SUITE(name) { /* test code */ }

// Run a test suite
RUN_SUITE(name);

// Assert condition
TEST_ASSERT(condition, "message");
```

## Running Tests

### Basic Usage

```bash
cd tests
make test
```

### Build Options

```bash
make          # Build test executable
make clean    # Remove object files only
make fclean   # Remove object files and executable
make re       # Clean and rebuild everything
make valgrind # Run tests with Valgrind memory checker
```

## Test Coverage

### malloc() Tests (8 test suites, 23 assertions)

✓ **malloc_basic** - Basic allocation and munmap
✓ **malloc_zero_size** - Verify NULL returned for size 0
✓ **malloc_small_allocation** - Verify page alignment for small allocations
✓ **malloc_large_allocation** - Allocate 1MB and verify
✓ **malloc_multiple_allocations** - Multiple simultaneous allocations
✓ **malloc_memory_access** - Read/write operations on allocated memory
✓ **malloc_sequential_allocations** - Independence of sequential allocations
✓ **malloc_edge_cases** - 1 byte, 4096 bytes, 10MB allocations

### free() Tests (5 test suites)

- **free_basic** - Basic free operation (pending implementation)
- **free_null_pointer** - Safe NULL pointer handling
- **free_multiple_allocations** - Multiple free operations (pending implementation)
- **free_sequential_malloc_free** - Repeated malloc/free cycles (pending implementation)
- **free_various_sizes** - Freeing different size allocations (pending implementation)

### realloc() Tests (5 test suites)

- **realloc_basic** - realloc with NULL pointer (pending implementation)
- **realloc_zero_size** - realloc with zero size (pending implementation)
- **realloc_shrink** - Resizing to smaller allocation (pending implementation)
- **realloc_grow** - Resizing to larger allocation (pending implementation)
- **realloc_multiple_times** - Multiple sequential realloc calls (pending implementation)

## Test Output

### Successful Test Run

```
╔════════════════════════════════════════╗
║    Malloc Implementation Test Suite    ║
╚════════════════════════════════════════╝

=== Testing malloc_basic ===
  ✓ PASS: malloc(100) should not return NULL

...

========================================
Test Summary
========================================
Total Tests Run:   23
Tests Passed:      23
Tests Failed:      0
========================================
✓ All tests passed!
========================================
```

## Implementation Guidance

### malloc() Status
✅ **IMPLEMENTED** - Currently returns page-aligned memory via mmap

### free() Implementation

Your free() should:
1. Accept NULL safely (no operation)
2. Track allocated regions (you'll need a metadata structure)
3. Call `munmap()` to return memory to the system
4. Handle edge cases gracefully

Example structure for tracking allocations:
```c
typedef struct s_block {
    size_t          size;
    struct s_block *next;
    void           *ptr;
} t_block;
```

### realloc() Implementation

Your realloc() should:
1. If ptr is NULL, act like malloc()
2. If size is 0, act like free() and return NULL
3. If size is same, return ptr
4. If size is smaller, potentially return same pointer
5. If size is larger, allocate new memory, copy data, free old memory

## Building Custom Tests

To add more tests, follow this pattern:

```c
#include "test.h"

TEST_SUITE(my_test_name)
{
    // Setup
    void *ptr = malloc(100);
    
    // Test
    TEST_ASSERT(ptr != NULL, "malloc should succeed");
    
    // Cleanup
    munmap(ptr, 100);
}
```

Then add to test_runner.c:
```c
void run_test_suite_my_test_name(void);

int main(void)
{
    // ...
    RUN_SUITE(my_test_name);
    // ...
}
```

## Debugging Tests

### Using Valgrind

```bash
make valgrind
```

This runs the test suite with Valgrind to detect:
- Memory leaks
- Invalid memory access
- Use-after-free bugs

### Manual Debugging

```bash
cd tests
make clean
make
lldb ./test_malloc  # macOS
gdb ./test_malloc   # Linux
```

### Enabling Verbose Output

Modify the test.h `TEST_ASSERT` macro to print more details:
```c
#define TEST_ASSERT(condition, message) \
    do { \
        g_tests_run++; \
        printf("Testing: %s\n", message); \
        if (!(condition)) { \
            printf("  ✗ FAIL\n"); \
            g_tests_failed++; \
        } else { \
            printf("  ✓ PASS\n"); \
            g_tests_passed++; \
        } \
    } while (0)
```

## Common Issues

### "pointer being freed was not allocated"

This occurs when:
- free() is called but not implemented
- Wrong pointer passed to free()
- Double free

**Solution**: Implement free() to properly track and manage allocated blocks

### Memory not readable/writable after allocation

This can occur if:
- mmap() failed (returned MAP_FAILED)
- Memory protection flags are incorrect

**Solution**: Verify malloc.c has correct mmap flags:
```c
PROT_READ | PROT_WRITE   // Readable and writable
MAP_ANONYMOUS | MAP_PRIVATE  // Anonymous, private mapping
```

### Segmentation fault

Possible causes:
- Writing beyond allocated block size
- Using unmapped memory
- Incorrect munmap() parameters

**Solution**: Use valgrind to pinpoint the exact location

## Performance Considerations

### Current malloc() Performance

Using mmap directly:
- **Advantages**: Simple, page-aligned, each allocation is independent
- **Disadvantages**: Overhead for small allocations, memory fragmentation

### Optimization Ideas

For better performance in free() and realloc():
1. Implement allocation pooling
2. Use a free list to track deallocated regions
3. Combine adjacent free blocks
4. Cache allocation metadata efficiently

## Integration

Once implemented and tested, your malloc can be used by:

1. Compiling the library: `make -C tests all`
2. Linking against test_malloc (or extracting the implementations)
3. Using malloc() from your code:
   ```c
   #include "src/malloc/malloc.h"
   void *ptr = malloc(100);
   ```

## Exit Codes

- `0` - All tests passed
- `1` - One or more tests failed

This allows CI/CD integration:
```bash
cd tests && make test || exit 1
```

## Notes

- Tests use `munmap()` directly to clean up malloc() allocations
- Once free() is implemented, tests will verify it instead of using munmap()
- The test framework is minimal and intentionally simple for learning purposes
- All tests are self-contained and can run independently

