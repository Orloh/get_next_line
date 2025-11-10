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

# All mandatory testfiles
MANDATORY_SRCS	= $(filter-out %_bonus.c, $(wildcard $(SRC_DIR)/test_*.c))
MANDATORY_BINS	=$(patsubst $(SRC_DIR)/%.c,%,$(MANDATORY_SRCS))

# Bonus test files
BONUS_SRCS	= $(wildcard $(SRC_DIR)/test_*_bonus.c)
BONUS_BINS	= $(patsubst $(SRC_DIR)/%.c,%,$(BONUS_SRCS))

# All binaries
ALL_BINS 	= $(MANDATORY_BINS) $(BONUS_BINS)

# Library sources
MANDATORY_GNL	= $(ROOT)/get_next_line.c $(ROOT)/get_next_line_utils.c
BONUS_GNL	= $(ROOT)/get_next_line_bonus.c $(ROOT)/get_next_line_utils_bonus.c

# Default test
DEFAULT_TEST = $(firstword $(MANDATORY_BINS))
DEFAULT_SRC = $(DEFAULT_TEST).c

# Phony targets
.PHONY: all run clean fclean re $(ALL_BINS) help bonus

# Build all tests
all: bonus mandatory

$(MANDATORY_BINS): %: $(SRC_DIR)/%.c
	@echo "=== Building mandatory test: $@ ==="
	@echo "  [MANDATORY MODE]"
	$(CC) $(CFLAGS) $(INC) $(MANDATORY_GNL) $(UNITY_DIR)/src/unity.c $< -o $@;
	@echo "=== Running $@==="
	./$@

mandatory: $(MANDATORY_BINS)

$(BONUS_BINS): %: $(SRC_DIR)/%.c
	@echo "=== Building bonus test: $@ ==="
	@echo "  [BONUS MODE]"
	$(CC) $(CFLAGS) $(INC) $(BONUS_GNL) $(UNITY_DIR)/src/unity.c $< -o $@;
	@echo "=== Running $@==="
	./$@

bonus: $(BONUS_BINS)

# Run default test
run: $(DEFAULT_TEST)

clean:
	@echo "Removing test binaries..."
	rm -f $(ALL_BINS)

fclean: clean
	@echo "Removing temporary files..."
	rm -f /tmp/testfile.*

re: fclean all

# Help

# ---------- Help ------------------------------------------------------------ #
help:
	@echo "Available targets:"
	@echo "  make                → build & run the first test ($(DEFAULT_TEST))"
	@echo "  make all            → build & run mandatory + bonus"
	@echo "  make mandatory      → build & run all mandatory tests"
	@echo "  make bonus          → build & run all bonus tests"
	@echo "  make run            → run the default test"
	@echo "  make clean/fclean   → remove binaries / temp files"
	@echo ""
	@echo "Mandatory test files:"
	@printf "  - %s\n" $(MANDATORY_BINS) 2>/dev/null || echo "  (none)"
	@echo "Mandatory test files:"
	@printf "  - %s\n" $(BONUS_BINS) 2>/dev/null || echo "  (none)"

