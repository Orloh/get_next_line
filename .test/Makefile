# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: orhernan <ohercelli@gmail.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/03 20:20:41 by orhernan          #+#    #+#              #
#    Updated: 2025/11/03 23:25:15 by orhernan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = test_extract_new_line
BUFFER_SIZE = 7
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g3 -O0 -D BUFFER_SIZE=$(BUFFER_SIZE)
SRC         = $(NAME).c	../get_next_line.c	\
	      ../get_next_line_utils.c	unity/src/unity.c
INC         = -I.. -Iunity/src

$(NAME): $(SRC)
	$(CC) $(CFLAGS) $(SRC) $(INC) -o $@

run: $(NAME)
	./$(NAME)

clean:
	rm -f $(NAME) /tmp/testfile.*

.PHONY: run clean
