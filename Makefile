# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: francema <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/07 14:36:23 by francema          #+#    #+#              #
#    Updated: 2025/05/20 18:17:19 by francema         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c prompt.c errors.c env_var.c parsing.c utils.c \

TOK_SRC = and_case.c double_quotes_case.c single_quotes_case.c \
		pipe_case.c redi_case.c subshell_case.c tok_dollar_case.c \
		tokenization.c word_case.c wildcard_case.c \

BUILTIN_SRC = ft_echo.c ft_env.c ft_exit.c ft_pwd.c \

SIG_SRC = ctrl_d.c setup_sig_handler.c signal_handler.c \

OBJ = $(SRC:.c=.o)

TOK_OBJ = $(addprefix tokenization/, $(TOK_SRC:.c=.o))

BUILTIN_OBJ = $(addprefix builtins/, $(BUILTIN_SRC:.c=.o))

SIG_SRC_OBJ = $(addprefix signals/, $(SIG_SRC:.c=.o))

CC = clang

CFLAGS = -Wall -Wextra -Werror -g

NAME = minishell

LIBFT = libft/libft.a

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C libft

$(NAME): $(OBJ) $(TOK_OBJ) $(BUILTIN_OBJ) $(SIG_SRC_OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -lreadline -o $(NAME) $^

clean:
	rm -f $(OBJ) $(TOK_OBJ) $(BUILTIN_OBJ) $(SIG_SRC_OBJ)
	make clean -C libft

fclean: clean
	rm -f $(NAME)
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re
