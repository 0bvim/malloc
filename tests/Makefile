# Test Makefile for malloc implementation

CC = gcc
CFLAGS = -Wall -Wextra -g -O0
LDFLAGS = -L..

TEST_DIR = .
SRC_DIR = ../src
LIBFT_DIR = ../libft

# Source files
MALLOC_SRC = $(SRC_DIR)/malloc/malloc.c
FREE_SRC = $(SRC_DIR)/free/free.c
REALLOC_SRC = $(SRC_DIR)/realloc/realloc.c

TEST_SRCS = $(TEST_DIR)/test_malloc.c \
            $(TEST_DIR)/test_free.c \
            $(TEST_DIR)/test_realloc.c \
            $(TEST_DIR)/test_runner.c

# Libft library
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_INCLUDE = -I$(LIBFT_DIR)/includes

# Include paths
INCLUDES = -I$(SRC_DIR) \
           -I$(SRC_DIR)/malloc \
           -I$(SRC_DIR)/free \
           -I$(SRC_DIR)/realloc \
           $(LIBFT_INCLUDE)

# Output
TEST_EXECUTABLE = test_malloc

# Object files
MALLOC_OBJ = malloc.o
FREE_OBJ = free.o
REALLOC_OBJ = realloc.o
TEST_OBJS = $(TEST_SRCS:.c=.o)

.PHONY: all clean fclean test valgrind

all: $(TEST_EXECUTABLE)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MALLOC_OBJ): $(MALLOC_SRC)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(FREE_OBJ): $(FREE_SRC)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(REALLOC_OBJ): $(REALLOC_SRC)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(TEST_EXECUTABLE): $(LIBFT) $(MALLOC_OBJ) $(FREE_OBJ) $(REALLOC_OBJ) $(TEST_OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -L$(LIBFT_DIR) -lft -o $@

test: $(TEST_EXECUTABLE)
	./$(TEST_EXECUTABLE)

valgrind: $(TEST_EXECUTABLE)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TEST_EXECUTABLE)

clean:
	rm -f $(MALLOC_OBJ) $(FREE_OBJ) $(REALLOC_OBJ) $(TEST_OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(TEST_EXECUTABLE)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean test valgrind re

