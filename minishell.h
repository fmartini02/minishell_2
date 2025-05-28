/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:33:55 by francema          #+#    #+#             */
/*   Updated: 2025/05/21 15:53:22 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define _POSIX_C_SOURCE 200809L
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
# include <termios.h>
# include <errno.h>
# include <limits.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <curses.h>
# include <term.h>
#include "libft/libft.h"

extern volatile sig_atomic_t sig_code;

typedef enum e_node_type
{
	NODE_CMD,
	NODE_PIPELINE,
	NODE_AND,
	NODE_OR,
	NODE_SUBSHELL
}	t_node_type;

typedef enum e_redir_type
{
	REDIR_INPUT,// <
	REDIR_OUTPUT,// >
	REDIR_APPEND,// >>
	REDIR_HEREDOC// <<
}	t_redir_type;

//t_redirection represents redirection operators with targets
typedef struct s_redirection
{
	t_redir_type			type;
	char					*target;    // filename or here-doc delimiter
	struct s_redirection	*next;
}	t_redirection;

typedef struct s_cmd_info
{
	char			*cmd_name;
	char			**cmd_args;
	t_redirection	*redirections;
}	t_cmd_info;

/*t_ast_node forms the parse tree, handling logical operators, pipelines, commands, and subshells.*/
typedef struct s_ast_node
{
	t_node_type			type;
	void				*content;// points to t_cmd_info, t_pipeline, or subtree for subshell
	struct s_ast_node	*left;// left child for &&, || operators
	struct s_ast_node	*right;// right child for &&, || operators
	struct s_ast_node	*next;// next command in a pipeline
}	t_ast_node;

/*t_pipeline groups commands linked by pipes.*/
typedef struct s_pipeline
{
	struct s_ast_node	*commands;  // linked list of commands or subshells
}	t_pipeline;

typedef struct s_mini
{
	char		*input;
	char		**envp;
	int			subshell_flag;
	int			last_exit_code;
	t_list		*env;
	t_list		*tok_input;
	t_cmd_info	*cmd_info;
	t_ast_node	*ast_root;// root of the parse tree
}	t_mini;

// errors.c
void	ft_fatal_memerr(t_mini *shell);

//BUILTINS
void	ft_echo(t_mini *shell);
void	ft_env(t_mini *shell);
void	ft_exit(t_mini *shell, char **args);
void	ft_pwd(t_mini *shell);
void	ft_cd(t_mini *shell);
void	ft_export(t_mini *shell);
void	ft_unset(t_mini *shell);

// env_var.c
char	*ft_dollar_case(t_mini *shell, char *str, size_t *i);
char	*get_env_value(t_mini *shell, const char *var_name);

// prompt.c
char	*get_prompt(void);

// parsing.c

// utils.c
int 	is_all_spaces(const char *str);
bool	ft_ispecial_char(char c);

//SIGNALS
void	ctrl_d_case(t_mini *shell);
void	setup_sig_handler(int is_interactive);
void	signal_handler(int sig);

//TOKENIZATION
char	*and_case(t_mini *shell, char *content, size_t *i);
char	*double_quotes_case(t_mini *shell, char *content, size_t *i);
char	*pipe_char_case(t_mini *shell, char *content, size_t *i);
char	*redi_case(t_mini *shell, char *content, size_t *i);
char	*single_quotes_case(t_mini *shell, char *content, size_t *i);
char	*subshell_case(t_mini *shell, char *content, size_t *i);
char	*tok_dollar_case(t_mini *shell, size_t *i, char *content);
void	tokenize_input(t_mini *shell);
char	*word_case(t_mini *shell, char *content, size_t *i);
char	*wildcard_case(t_mini *shell, char *content, size_t *i);

#endif
