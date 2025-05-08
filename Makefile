# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: francema <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/07 14:36:23 by francema          #+#    #+#              #
#    Updated: 2025/05/07 17:03:20 by francema         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c ft_exit.c prompt.c \

OBJ = $(SRC:.c=.o)

CC = clang

CFLAGS = -Wall -Wextra -Werror -g

NAME = minishell

LIBFT = libft/libft.a

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C libft

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) -lreadline -o $(NAME) $(OBJ) $(LIBFT)

clean:
	rm -f $(OBJ)
	make clean -C libft

fclean: clean
	rm -f $(NAME)
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re
