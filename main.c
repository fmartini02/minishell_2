/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalloli <mdalloli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:30:45 by francema          #+#    #+#             */
/*   Updated: 2025/07/01 19:15:36 by mdalloli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sig_code = 0;

/* Process of the command */
void	parsing(t_mini *shell)
{
	t_tok_lst	*head;

	if (!tokenize_input(shell))
	{
		if (shell)
			cleanup_shell(shell, -1);
		return ;
	}
	head = shell->tok_input;
	ast_init(shell);
	shell->tok_input = head;
	execute_ast(shell->ast_root, shell);
}

/* Initializes a linked list of environment variabiles */
t_list	*init_env(char **env)
{
	t_list	*head;
	int		i;

	if (env[0])
		head = ft_lstnew((void *) ft_strdup(env[0]));
	else
		return (NULL);
	i = 1;
	while (env[i])
	{
		ft_lstadd_back(&head, ft_lstnew(ft_strdup(env[i])));
		i++;
	}
	return (head);
}

void	init_shell(t_mini *shell, char **envp)
{
	rl_catch_signals = 0;
	shell->envp = envp;
	shell->env = init_env(envp);
	shell->last_exit_code = 0;
	shell->input = NULL;
	shell->cmd_info = NULL;
	shell->tok_input = NULL;
	shell->ast_root = NULL;
	shell->err_print = false;
	shell->unit = NULL;
	if (!shell->env)
		ft_fatal_memerr(shell);
}

void	loop_shell(t_mini *shell)
{
	while (1)
	{
		shell->prompt = get_prompt();
		if (!shell->prompt)
			shell->prompt = ft_strdup("minishell$ ");
		g_sig_code = -42;
		shell->input = readline(shell->prompt);
		g_sig_code = 0;
		if (!shell->input)
			ctrl_d_case(shell);
		if (shell->input[0] == '\0' || is_all_spaces(shell->input))
		{
			free(shell->input);
			free(shell->prompt);
			continue ;
		}
		add_history(shell->input);
		parsing(shell);
		shell->err_print = false;
		cleanup_shell(shell, -1);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_mini	shell;

	(void)av;
	(void)ac;
	init_shell(&shell, envp);
	setup_sig_handler();
	loop_shell(&shell);
}
