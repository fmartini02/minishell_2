/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:33:55 by francema          #+#    #+#             */
/*   Updated: 2025/07/15 14:01:38 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define _POSIX_C_SOURCE 200809L
# include <unistd.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
# include <termios.h>
# include <errno.h>
# include <limits.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <curses.h>
# include <term.h>
# include "libft/libft.h"

# define VAR_NOT_FOUND 2
# define IS_SPACE 69
# define SUCCESS 10

extern volatile sig_atomic_t	g_sig_code;

// needed during tokenization
typedef enum e_tok_type
{
	WORD,
	PIPE,
	REDIRECT,
	AND,
	OR,
	SUBSHELL,
	DOUBLE_QUOTES,
	SINGLE_QUOTES,
	WILDCARD,
	DOLLAR,
}	t_tok_type;

// t_node_type represents the type of AST node
typedef enum e_node_type
{
	NODE_CMD,
	NODE_PIPELINE,
	NODE_AND,
	NODE_OR,
	NODE_SUBSHELL
}	t_node_type;

/* <, >, >>, <<*/
typedef enum e_redir_type
{
	REDIR_INPUT,
	REDIR_OUTPUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}	t_redir_type;

/* t_redirection represents redirection operators with
targets(filename or here-doc delimiter) */
typedef struct s_redirection
{
	t_redir_type			type;
	char					*target;
	bool					flag_here_doc;
	struct s_redirection	*next;
	int						heredoc_fd;
}	t_redirection;

/* t_exec_unit Represents an executable command unit
extracted from an AST node */
typedef struct s_exec_unit
{
	char			**argv;
	t_redirection	*redirs;
}	t_exec_unit;

typedef struct s_cmd_info
{
	char			*cmd_name;
	char			**cmd_args;
	t_redirection	*redirections;
}	t_cmd_info;

/* t_ast_node forms the parse tree, handling logical operators,
pipelines, commands, and subshells.*/
typedef struct s_ast_node
{
	t_node_type			type;
	void				*content;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
	struct s_ast_node	*next;
}	t_ast_node;

/* t_pipeline groups commands linked by pipes.*/
typedef struct s_pipeline
{
	struct s_ast_node	*commands;
}	t_pipeline;

typedef struct s_tok_lst
{
	char				*content;
	int					type;
	char				*tok_name;
	struct s_tok_lst	*next;
}	t_tok_lst;

typedef struct s_mini
{
	char		*input;
	char		**envp;
	int			last_exit_code;
	bool		err_print;
	char		*prompt;
	t_list		*env;
	t_tok_lst	*tok_input;
	t_cmd_info	*cmd_info;
	t_exec_unit	*unit;
	t_ast_node	*ast_root;
}	t_mini;

typedef struct s_pipeinfo
{
	int		**pipes;
	pid_t	*pids;
	int		idx;
	int		count;
	t_mini	*shell;
}	t_pipinfo;

//MEMORY MANAGEMENT
void		ft_fatal_memerr(t_mini *shell);
void		free_exec_unit(t_exec_unit *unit);
void		cleanup_shell(t_mini *shell, int exit_code);
char		**free_partial_array(char **arr, int last_index);
void		free_env(t_mini *shell);
void		free_pipes(t_pipinfo *info);

//BUILTINS
void		ft_echo(char **args, t_mini *shell);
void		ft_env(t_mini *shell, char **args);
void		ft_exit(t_mini *shell, char **args, t_pipinfo *info);
void		ft_pwd(t_mini *shell, char **args);
void		ft_cd(char **args, t_mini *shell);
void		ft_export(t_mini *shell, char **args);
void		ft_unset(t_mini *shell, char **args);
//BUILTINS builtin helpers
bool		is_builtin(const char *cmd);
void		change_dir_and_update(t_mini *shell, char *oldpwd, char *path);
void		ft_sort_strarr(char **arr);
void		print_sorted_env(t_list *env);

//DOLLAR EXPANSION
char		*ft_dollar_case(t_mini *shell, char *str, size_t *i);
char		*get_env_value(t_mini *shell, const char *var_name);
char		*handle_special_dollar_cases(t_mini *shell, char *str, size_t *i);
char		*extract_var_name(char *str, size_t start, size_t *end);
void		apply_doll_exansion(int write_fd, char *line, t_mini *shell);
int			append_double_wuote_token(t_mini *shell, char *content);

//REDIRECTIONS
int			apply_redirections(t_exec_unit *unit, t_mini *shell);
int			open_redir_fd(t_redirection *redir);
int			handle_input_redirection(
				t_redirection *redir, t_mini *shell, int *last_in);
int			handle_output_redirection(t_redirection *redir, t_mini *shell);
//REDIRECTIONS heredoc
void		handle_eventual_heredoc(t_ast_node *node, t_mini *shell);
int			handle_heredoc(t_redirection *redir);
int			prepare_heredocs(t_ast_node *ast, t_mini *shell);
int			heredoc_read_loop(
				int pip_fd, char *eof, struct sigaction *old_sa, t_mini *shell);
void		close_all_heredoc_fds(t_ast_node *ast);
//REDIRECTIONS heredoc signals
void		heredoc_sigint_handler(int sig);
void		write_ctrld(const char *delimiter);
int			sigaction_return(struct sigaction *old_sa, int ret_value);

//AST-PARSING
void		ast_init(t_mini *shell);
void		print_ast(t_ast_node *node, int depth);
t_ast_node	*parse_cmd_line(t_mini *shell, t_tok_lst **tokens);
t_ast_node	*parse_pipeline(t_mini *shell, t_tok_lst **tokens);
bool		parse_redirection(
				t_tok_lst **tokens, t_cmd_info *cmd, t_mini *shell);
t_cmd_info	*add_arg_to_cmd(t_cmd_info *cmd, char *arg);
char		**add_arg_to_array(char **args, char *new_arg);
bool		handle_redirections(
				t_tok_lst **tokens, t_cmd_info *cmd, t_mini *shell);
t_ast_node	*parse_simple_cmd(t_mini *shell, t_tok_lst **tokens);
t_ast_node	*parse_subshell(t_mini *shell, t_tok_lst **tokens);
void		free_ast(t_ast_node *node);
void		free_redirections(t_redirection *redir);
int			is_control_operator(char *token);
void		free_cmd_info(t_cmd_info *cmd);
bool		is_valid_token(t_tok_lst **tokens);
void		print_unexpected_token(t_tok_lst **tokens);

//EXECUTION
void		execute_ast(t_ast_node *node, t_mini *shell);
void		execute_exec_unit(t_exec_unit *unit, t_mini *shell);
void		child_process(t_exec_unit *unit, t_mini *shell, t_pipinfo *info);
char		*get_path_command(t_mini *shell, const char *cmd);
//EXECUTION execute_builtin.c
int			execute_builtin(t_exec_unit *unit, t_mini *shell, t_pipinfo *info);
int			chose_builtin(t_exec_unit *unit, t_mini *shell,
				bool is_parent, t_pipinfo *info);
bool		is_cd_export_unset_exit(const char *cmd);
//EXECUTION extraction.c
t_exec_unit	*extract_exec_units(t_ast_node *node);

//PIPELINE
char		**env_list_to_array(t_list *env);
t_ast_node	*pipeline_loop(t_ast_node **left, t_ast_node **right,
				t_mini *shell, t_tok_lst **tokens);
t_ast_node	*create_pipeline_node(t_ast_node *left, t_ast_node *right);
t_ast_node	*operator_case(t_ast_node **left, t_mini *shell,
				t_tok_lst **tokens, t_ast_node *right);
void		free_info(t_pipinfo *info);
void		close_all_pipes(int **pipes, int count);
int			count_pipeline_commands(t_ast_node *cmd_list);
int			**create_pipes(int count);
void		child_pipeline(t_ast_node *node, t_pipinfo *info);
void		execute_pipeline(t_ast_node *cmds, t_mini *shell);

// utils.c
int			is_all_spaces(const char *str);
bool		ft_ispecial_char(char c);
bool		append_partial_str(char **res, size_t start,
				size_t len, t_mini *shell);
char		*get_prompt(t_mini *shell);

//SIGNALS
void		ctrl_d_case(t_mini *shell);
void		setup_sig_handler(void);
void		signal_handler(int sig);
void		setup_heredoc_signals(struct sigaction *old_sa);

//TOKENIZATION
bool		tokenize_input(t_mini *shell);
//TOKENIZATION cases
int			andpersand_case(t_mini *shell, char *content, size_t *i);
int			double_quotes_case(t_mini *shell, char *content, size_t *i);
int			pipe_char_case(t_mini *shell, char *content, size_t *i);
int			redi_case(t_mini *shell, char *content, size_t *i);
int			single_quotes_case(t_mini *shell, char *content, size_t *i);
int			subshell_case(t_mini *shell, char *content, size_t *i);
int			word_case(t_mini *shell, char *content, size_t *i);
int			wildcard_case(t_mini *shell, char *content, size_t *i);
//TOKENIZATION single_quotes_cases helpers
char		*handle_empty_or_unpaired_single_quotes(char *s, size_t *i);
bool		validate_single_quote_closure(t_mini *shell, char *s, size_t i);
char		*extract_single_quote_content(t_mini *shell, size_t start,
				size_t end, bool eof);
int			append_single_quote_token(t_mini *shell, char *content);
bool		process_quoted(char **res, size_t *i, char quote, t_mini *shell);
//TOKENIZATION double_quotes_cases helpers
bool		handle_closing_double_quote(t_mini *shell, char *in, size_t *i);
void		append_substr(char **to_print, char *line,
				size_t start, size_t end);
void		handle_double_quotes(char *line, size_t *i,
				char **to_print, t_mini *shell);
bool		is_eof(char *s, size_t i);
//TOKENIZATION token merging helper
char		*to_join(char *s, size_t *i, t_mini *shell);
char		*append_var(char *line, size_t *i, char *to_print, t_mini *shell);
char		*token_join(char *content, t_mini *shell, size_t *i);
//TOKENIZATION append node to list
void		append_word_node(t_mini *shell, char *content);
void		add_back_tok_lst(t_tok_lst **head, t_tok_lst *new_node);
t_tok_lst	*new_tok_lst(char *content, t_tok_type type, char *tok_name);
t_tok_lst	*last_token(t_tok_lst *head);
void		free_tok_lst(t_tok_lst *head);
void		print_tok_lst(t_tok_lst *head);
//TOKENIZATION dollar handlers
void		expand_doll(t_mini *shell, char *in);
void		handle_ambiguous_redirect(t_mini *shell, size_t *i, char **res);
void		handle_dollar_expansion(t_mini *shell, size_t *i,
				char **res, size_t *start);
bool		handle_dollar_inside_quotes(t_mini *shell, size_t *i,
				char **res, size_t *start);
bool		is_word_delimiter(char c);
bool		should_print_doll_char(char *s, size_t *i);

#endif
