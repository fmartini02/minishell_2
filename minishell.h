/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:33:55 by francema          #+#    #+#             */
/*   Updated: 2025/07/04 19:05:21 by francema         ###   ########.fr       */
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
}	t_pipeinfo;

// free_errors.c
void		ft_fatal_memerr(t_mini *shell);
void		free_exec_unit(t_exec_unit *unit);
void		cleanup_shell(t_mini *shell, int exit_code);

//BUILTINS
void		ft_echo(char **args, t_mini *shell);
void		ft_env(t_mini *shell, char **args);
void		ft_exit(t_mini *shell, char **args, bool is_parent);
void		ft_pwd(t_mini *shell, char **args);
void		ft_cd(char **args, t_mini *shell);
void		ft_export(t_mini *shell, char **args);
void		ft_unset(t_mini *shell, char **args);

// env_var.c
char		*ft_dollar_case(t_mini *shell, char *str, size_t *i);
char		*get_env_value(t_mini *shell, const char *var_name);

// prompt.c
char		*get_prompt(void);

// redirections.c
int			apply_redirections(t_exec_unit *unit, t_mini *shell);

// handle_redirections.c
int			handle_input_redirection(t_redirection *redir,
				t_mini *shell, int *last_in);
int			handle_output_redirection(t_redirection *redir,
				t_mini *shell);
int			handle_heredoc(t_redirection *redir);

// prepare_heredocs.c
int			prepare_heredocs(t_ast_node *ast);
void		heredoc_sigint_handler(int sig);
void		write_ctrld(const char *delimiter);
void		prepare_and_check_heredocs(t_ast_node *node);
int			sigaction_return(struct sigaction *old_sa, int ret_value);

// close_heredocs_fds.c
void		close_all_heredoc_fds(t_ast_node *ast);

//AST-PARSING
void		ast_init(t_mini *shell);
void		print_ast(t_ast_node *node, int depth);
t_ast_node	*parse_cmd_line(t_mini *shell, t_tok_lst **tokens);
t_ast_node	*parse_pipeline(t_mini *shell, t_tok_lst **tokens);
bool		parse_redirection(t_tok_lst **tokens, t_cmd_info *cmd,
				t_mini *shell);
t_cmd_info	*add_arg_to_cmd(t_cmd_info *cmd, char *arg);
char		**add_arg_to_array(char **args, char *new_arg);
bool		handle_redirections(t_tok_lst **tokens, t_cmd_info *cmd,
				t_mini *shell);
t_ast_node	*parse_simple_cmd(t_mini *shell, t_tok_lst **tokens);
t_ast_node	*parse_subshell(t_mini *shell, t_tok_lst **tokens);
void		free_ast(t_ast_node *node);
void		free_redirections(t_redirection *redir);
int			is_control_operator(char *token);
void		free_cmd_info(t_cmd_info *cmd);
bool		is_valid_token(t_tok_lst **tokens);
void		print_unexpected_token(t_tok_lst **tokens);

// extraction.c
t_exec_unit	*extract_exec_units(t_ast_node *node);

// execution.c
void		execute_exec_unit(t_exec_unit *unit, t_mini *shell);
void		execute_ast(t_ast_node *node, t_mini *shell);
void		child_process(t_exec_unit *unit, t_mini *shell);

// execution_utils.c
void		exit_command_not_found(t_exec_unit *unit);
void		free_split(char **arr);
char		*get_path_command(t_mini *shell, const char *cmd);

// execute_builtin.c
int			execute_builtin(t_exec_unit *unit, t_mini *shell, bool is_parent);
int			handle_critical_builtin(t_exec_unit *unit, t_mini *shell);

//PIPELINE
char		**env_list_to_array(t_list *env);
void		close_all_pipes(int **pipes, int count);
void		free_pipes(int **pipes, int count);
int			count_pipeline_commands(t_ast_node *cmd_list);
int			**create_pipes(int count);
void		child_pipeline(t_ast_node *node, t_pipeinfo *info);
void		execute_pipeline(t_ast_node *cmds, t_mini *shell);

// utils.c
int			is_all_spaces(const char *str);
bool		ft_ispecial_char(char c);
bool		is_builtin(const char *cmd);
void		ft_sort_strarr(char **arr);

//SIGNALS
void		ctrl_d_case(t_mini *shell);
void		setup_sig_handler(void);
void		signal_handler(int sig);

//TOKENIZATION
int			and_case(t_mini *shell, char *content, size_t *i);
char		*get_var_name(char *s, char *content, size_t *i, t_mini *shell);
int			append_var(char *var_value, char *var_name, t_mini *shell, int j);
int			double_quotes_case(t_mini *shell, char *content, size_t *i);
int			pipe_char_case(t_mini *shell, char *content, size_t *i);
bool		is_word_delimiter(char c);
int			redi_case(t_mini *shell, char *content, size_t *i);
int			single_quotes_case(t_mini *shell, char *content, size_t *i);
int			subshell_case(t_mini *shell, char *content, size_t *i);
size_t		get_doll_indx(char *s, size_t i);
int			tok_dollar_case(t_mini *shell, size_t *i, char *content);
bool		tokenize_input(t_mini *shell);
int			check_tok_front(t_mini *shell, size_t *i);
int			check_tok_back(t_mini *shell, size_t *i, bool is_dollar);
int			word_case(t_mini *shell, char *content, size_t *i);
int			wildcard_case(t_mini *shell, char *content, size_t *i);
void		add_back_tok_lst(t_tok_lst **head, t_tok_lst *new_node);
t_tok_lst	*new_tok_lst(char *content, t_tok_type type, char *tok_name);
t_tok_lst	*last_token(t_tok_lst *head);
void		free_tok_lst(t_tok_lst *head);
void		print_tok_lst(t_tok_lst *head);
size_t		get_end_indx(char *s, size_t doll_indx);
size_t		get_start_indx(char *s, size_t doll_indx);
size_t		get_doll_indx(char *s, size_t i);

#endif
