# Test README

## Running the Tests

### Basic Test Execution
```bash
cd tests
make test
```

### Clean Build and Test
```bash
cd tests
make re
make test
```

### Memory Leak Detection with Valgrind
```bash
cd tests
make valgrind
```

### Clean Up
```bash
cd tests
make clean    # Remove object files
make fclean   # Remove everything including executable
```

## Test Coverage

### malloc() Tests
- **malloc_basic**: Basic allocation and deallocation
- **malloc_zero_size**: Verify NULL is returned for zero size
- **malloc_small_allocation**: Small allocations with alignment check
- **malloc_large_allocation**: Large allocations (1MB)
- **malloc_multiple_allocations**: Multiple simultaneous allocations
- **malloc_memory_access**: Read/write operations on allocated memory
- **malloc_sequential_allocations**: Independence of sequential allocations
- **malloc_edge_cases**: Very small, page-sized, and large allocations

### free() Tests
- **free_basic**: Basic free operation
- **free_null_pointer**: Safe NULL pointer handling
- **free_multiple_allocations**: Multiple free operations
- **free_sequential_malloc_free**: Repeated malloc/free cycles (100 iterations)
- **free_various_sizes**: Freeing different size allocations

### realloc() Tests
- **realloc_basic**: realloc behavior with NULL pointer
- **realloc_zero_size**: realloc with zero size
- **realloc_shrink**: Resizing to smaller allocation
- **realloc_grow**: Resizing to larger allocation
- **realloc_multiple_times**: Multiple realloc calls

## Test Output Format

The test suite produces formatted output:
- ✓ PASS: Test passed
- ✗ FAIL: Test failed

Final summary shows:
- Total Tests Run
- Tests Passed
- Tests Failed
- Overall result

## Implementing free() and realloc()

Currently, free() and realloc() have empty implementations. You need to implement:

1. **free.c**: Implement to deallocate memory allocated by malloc
2. **realloc.c**: Implement to resize allocated memory regions

See the test expectations for the required behavior.

