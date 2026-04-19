#!/bin/bash
# Quick start script for running tests

set -e

echo "╔════════════════════════════════════════╗"
echo "║   Malloc Test Suite - Quick Start      ║"
echo "╚════════════════════════════════════════╝"
echo ""

cd "$(dirname "$0")"

# Parse arguments
case "${1:-test}" in
    test)
        echo "🔨 Building and running tests..."
        make test
        ;;
    build)
        echo "🔨 Building test executable..."
        make clean
        make
        echo "✓ Built: ./test_malloc"
        ;;
    clean)
        echo "🧹 Cleaning build artifacts..."
        make fclean
        echo "✓ Cleaned"
        ;;
    rebuild|re)
        echo "🔄 Rebuilding..."
        make re
        make test
        ;;
    valgrind|leak)
        echo "🔍 Running with Valgrind memory checker..."
        make valgrind
        ;;
    help|--help|-h)
        echo "Usage: $0 [command]"
        echo ""
        echo "Commands:"
        echo "  test     - Build and run tests (default)"
        echo "  build    - Build test executable only"
        echo "  rebuild  - Clean and rebuild everything"
        echo "  clean    - Remove build artifacts"
        echo "  valgrind - Run tests with memory leak detection"
        echo "  help     - Show this help message"
        echo ""
        echo "Examples:"
        echo "  $0 test"
        echo "  $0 valgrind"
        echo "  $0 rebuild"
        ;;
    *)
        echo "Unknown command: $1"
        echo "Use '$0 help' for usage information"
        exit 1
        ;;
esac

echo ""
echo "✓ Done!"

