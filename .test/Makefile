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

NAME        = test_read_from_file
BUFFER_SIZE = 5
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -D BUFFER_SIZE=$(BUFFER_SIZE)
SRC         = test_read_next_line.c	../get_next_line.c	\
	      ../get_next_line_utils.c	unity/src/unity.c
INC         = -I.. -Iunity/src

$(NAME): $(SRC)
	$(CC) $(CFLAGS) $(SRC) $(INC) -o $@

run: $(NAME)
	./$(NAME)

clean:
	rm -f $(NAME) /tmp/testfile.*

.PHONY: run clean
