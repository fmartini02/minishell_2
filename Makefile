# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: francema <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/07 14:36:23 by francema          #+#    #+#              #
#    Updated: 2025/07/01 19:38:46 by francema         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

SRC = main.c prompt.c free_errors.c env_var.c utils.c redirections.c \
	execution.c extraction.c execution_utils.c execute_builtin.c \
	prepare_heredocs.c handle_redirections.c close_heredoc_fds.c \
	cleanup_shell.c prepare_heredoc_utils.c \

TOK_SRC = and_case.c check_tok_back.c check_tok_front.c \
		double_quotes_case.c single_quotes_case.c pipe_case.c \
		redi_case.c subshell_case.c tok_dollar_case.c \
		tokenization.c word_case.c wildcard_case.c token_utils.c \
		get_var_name.c get_var_name_utils.c \

BUILTIN_SRC = ft_echo.c ft_env.c ft_exit.c ft_pwd.c ft_cd.c ft_export.c ft_unset.c \

SIG_SRC = ctrl_d.c setup_sig_handler.c signal_handler.c \

AST_SRC = ast_init.c ast_utils.c parse_cmd_line.c parse_pipeline.c \
		parse_redirection.c parse_simple_cmd.c parse_subshell.c print_ast.c \
		parse_simple_cmd_utils.c print_unexpected_token.c

PIPELINE_SRC = child_pipeline.c execute_pipeline.c pipeline_utils.c pipeline_utils2.c

OBJ = $(SRC:.c=.o)

TOK_OBJ = $(addprefix tokenization/, $(TOK_SRC:.c=.o))

BUILTIN_OBJ = $(addprefix builtins/, $(BUILTIN_SRC:.c=.o))

SIG_OBJ = $(addprefix signals/, $(SIG_SRC:.c=.o))

AST_OBJ = $(addprefix AST/, $(AST_SRC:.c=.o))

PIPELINE_OBJ = $(addprefix pipeline/, $(PIPELINE_SRC:.c=.o))

ALL_OBJS = $(OBJ) $(TOK_OBJ) $(BUILTIN_OBJ) $(SIG_OBJ) $(AST_OBJ) $(PIPELINE_OBJ)

CC = clang

CFLAGS = -Wall -Wextra -Werror -g

NAME = minishell

LIBFT = libft/libft.a

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C libft

$(NAME): $(ALL_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -lreadline -o $(NAME) $^

clean:
	rm -f $(ALL_OBJS)
	make clean -C libft

fclean: clean
	rm -f $(NAME)
	make fclean -C libft

re: fclean all

# valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --track-origins=yes --suppressions=ignore_readline.supp ./minishell

.PHONY: all clean fclean re
