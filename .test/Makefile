# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: orhernan <ohercelli@gmail.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/03 20:20:41 by orhernan          #+#    #+#              #
#    Updated: 2025/11/06 12:32:22 by orhernan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_BASE	= test_
BUFFER_SIZE	= 7
CC		= cc
CFLAGS		= -Wall -Wextra -Werror -g3 -O0 -D BUFFER_SIZE=$(BUFFER_SIZE)

# Paths relative to .test
SRC_DIR		= .
ROOT		= ..
UNITY_DIR	= $(SRC_DIR)/unity
INC		= -I$(ROOT) -I$(UNITY_DIR)/src

# All test files that start with test_
TEST_SRCS	= $(wildcard $(SRC_DIR)/test_*.c)

# Library sources
GNL_SRCS	= $(ROOT)/get_next_line.c $(ROOT)/get_next_line_utils.c

# Derived names
TEST_BINS	=$(patsubst $(SRC_DIR)/%.c,%,$(TEST_SRCS))

# Default test
DEFAULT_TEST = test_ft_read_from_file
DEFAULT_SRC = $(DEFAULT_TEST).c

# Phony targets
.PHONY: all run clean fclean re $(TEST_BINS) help

# Pattern rule: test_foo -> test_foo (binary)
$(TEST_BINS): %: $(SRC_DIR)/%.c
	@echo "=== Building $@ ==="
	$(CC) $(CFLAGS) $(INC) $(GNL_SRCS) $(UNITY_DIR)/src/unity.c $^ -o $@
	@echo "=== Running $@ ==="
	./$@

# Build all tests
all: $(TEST_BINS)

# Run default test
run:
	@echo "=== Building $(DEFAULT_TEST) ==="
	$(CC) $(CFLAGS) $(INC) $(GNL_SRCS) $(UNITY_DIR)/src/unity.c $(DEFAULT_SRC) -o $(DEFAULT_TEST)
	@echo "=== Running $(DEFAULT_TEST) ==="
	./$(DEFAULT_TEST)

clean:
	@echo "Removing test binaries..."
	rm -f $(TEST_BINS)

fclean: clean
	@echo "Removing temporary files..."
	rm -f /tmp/testfile.*

re: fclean all

# Help

# ---------- Help ------------------------------------------------------------ #
help:
	@echo "Available targets:"
	@echo "  make                → build & run the first test ($(DEFAULT_TEST))"
	@echo "  make all            → build every test"
	@echo "  make <test_name>    → build & run a specific test (e.g. make test_read_from_file)"
	@echo "  make run            → run the default test"
	@echo "  make clean/fclean   → remove binaries / temp files"
	@echo ""
	@echo "Current test files:"
	@ls -1 $(SRC_DIR)/test_*.c 2>/dev/null | sed 's|.*/|  - |' || echo "  (none)"

