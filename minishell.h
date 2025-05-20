/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:33:55 by francema          #+#    #+#             */
/*   Updated: 2025/05/20 15:21:59 by francema         ###   ########.fr       */
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

typedef struct s_cmd_info
{
	char	*cmd_name;
	char	**cmd_args;
	void	*next;
}	t_cmd_info;

typedef struct s_mini
{
	char		*input;
	char		**envp;
	int			subshell_flag;
	int			last_exit_code;
	t_list		*env;
	t_list		*tok_input;
	t_cmd_info	*cmd_info;
}	t_mini;

// errors.c
void	ft_fatal_memerr(t_mini *shell);

// builtin
void	ft_echo(t_mini *shell);
void	ft_env(t_mini *shell);
void	ft_exit(t_mini *shell, char **args);
void	ft_pwd(t_mini *shell);

// env_var.c
char	*ft_dollar_case(t_mini *shell, char *str, size_t *i);
char	*get_env_value(t_mini *shell, const char *var_name);

// prompt.c
char	*get_prompt(void);

// parsing.c

// utils.c
int 	is_all_spaces(const char *str);
bool	ft_ispecial_char(char c);

//TOKENIZATION
char	*and_case(t_mini *shell, char *content, size_t *i);
char	*double_quotes_case(t_mini *shell, char *content, size_t *i);
char	*pipe_char_case(t_mini *shell, char *content, size_t *i);
char	*redi_case(t_mini *shell, char *content, size_t *i);
char	*single_quotes_case(t_mini *shell, char *content, size_t *i);
char	*subshell_case(t_mini *shell, char *content, size_t *i);
char	*tok_dollar_case(t_mini *shell, size_t *i, char *content);
char	*word_case(t_mini *shell, char *content, size_t *i);
char	*wildcard_case(t_mini *shell, char *content, size_t *i);

#endif
