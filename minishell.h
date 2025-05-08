/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:33:55 by francema          #+#    #+#             */
/*   Updated: 2025/05/08 16:16:14 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define _POSIX_C_SOURCE 200809L
# include<unistd.h>
# include<stdio.h>
# include<stdlib.h>
# include<signal.h>
# include<fcntl.h>
# include<termios.h>
# include<errno.h>
# include<limits.h>
# include<sys/wait.h>
# include<readline/readline.h>
# include<readline/history.h>
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
	int			pip_trick[2];
	t_list		*env;
	t_list		*tok_input;
	t_cmd_info	*cmd_info;
}	t_mini;

void	ft_exit(t_mini *shell, char **args);

#endif
