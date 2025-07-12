NAME = minishell

CC = clang
CFLAGS = -Wall -Wextra -Werror -g

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
READLINE = -lreadline

# Source groups by directory
SRC_MAIN = main.c get_prompt.c shell_utils.c

SRC_AST = \
	AST/ast_init.c AST/ast_utils.c AST/parse_cmd_line.c AST/parse_pipeline.c \
	AST/parse_redirection.c AST/parse_simple_cmd.c AST/parse_simple_cmd_utils.c \
	AST/parse_subshell.c AST/pipeline_loop.c AST/print_ast.c AST/print_unexpected_token.c

SRC_BUILTINS = \
	builtins/cd_change_state.c builtins/export_print.c builtins/ft_cd.c \
	builtins/ft_echo.c builtins/ft_env.c builtins/ft_exit.c builtins/ft_export.c \
	builtins/ft_pwd.c builtins/ft_unset.c

SRC_EXECUTION = \
	execution/ast_extraction.c execution/check_path_to_cmd.c execution/child_proceses.c \
	execution/execute_ast.c execution/execute_builtin.c \
	execution/redirections/apply_redi.c execution/redirections/handle_fds.c

SRC_EXTRACT_DOLLAR = \
	extract_dollar/ft_dollar_case.c extract_dollar/parsing_var_name.c

SRC_FREE_MEM = \
	free_mem/cleanup_shell.c free_mem/free_ast_stuff.c free_mem/free_errors.c

SRC_HERE_DOC = \
	here_doc/doll_expansion_utils.c here_doc/here_doc_doll_expansion.c \
	here_doc/here_doc_signals.c here_doc/prepare_here_doc.c here_doc/read_loop.c

SRC_PIPELINE = \
	pipeline/child_pipeline.c pipeline/execute_pipeline.c \
	pipeline/env_for_execve.c pipeline/fds_for_pipes.c

SRC_SIGNALS = \
	signals/ctrl_d.c signals/setup_sig_handler.c signals/signal_handler.c

SRC_TOKEN_CASES = \
	tokenization/cases/andpersand_case.c tokenization/cases/double_quotes_case.c \
	tokenization/cases/pipe_case.c tokenization/cases/redi_case.c \
	tokenization/cases/single_quotes_case.c tokenization/cases/single_quotes_helpers.c \
	tokenization/cases/subshell_case.c tokenization/cases/wildcard_case.c \
	tokenization/cases/word_case.c

SRC_TOKEN_DOLLAR = \
	tokenization/first_doll_exapansion/ambiguous_redirect.c \
	tokenization/first_doll_exapansion/expand_doll.c \
	tokenization/first_doll_exapansion/first_expansion_double_quotes.c \
	tokenization/first_doll_exapansion/handle_dollar.c

SRC_TOKEN_MERGE = \
	tokenization/tokens_merge_logic/to_join.c \
	tokenization/tokens_merge_logic/to_join_quotes_stuff.c \
	tokenization/tokens_merge_logic/tokens_merge.c

SRC_TOKEN_OTHER = \
	tokenization/tokenization.c tokenization/t_tok_lst_function.c

SRC_TOKENIZATION = $(SRC_TOKEN_CASES) $(SRC_TOKEN_DOLLAR) $(SRC_TOKEN_MERGE) $(SRC_TOKEN_OTHER)

SRC_ALL = \
	$(SRC_MAIN) \
	$(SRC_AST) \
	$(SRC_BUILTINS) \
	$(SRC_EXECUTION) \
	$(SRC_EXTRACT_DOLLAR) \
	$(SRC_FREE_MEM) \
	$(SRC_HERE_DOC) \
	$(SRC_PIPELINE) \
	$(SRC_SIGNALS) \
	$(SRC_TOKENIZATION)

OBJ = $(SRC_ALL:.c=.o)

# Rules
all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LIBFT) $(READLINE)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes \
	--track-origins=yes --suppressions=ignore_readline.supp ./$(NAME)

.PHONY: all clean fclean re valgrind
