/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:30:45 by francema          #+#    #+#             */
/*   Updated: 2025/05/06 20:08:59 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t sig_code = 0;

void	parsing(t_mini *shell)
{
	add_history(shell->input);
	printf("%s\n", shell->input);
	free(shell->input);
}

void	ctrl_d_case(t_mini *shell)
{
	free(shell->input);
	ft_lstclear(&shell->env, free);
	exit(0);
}

t_list	*init_env(char **env)
{
	t_list	*head;
	int		i;

	if (env[0])
		head = ft_lstnew((void *) ft_strdup(env[0]));
	else
		return(NULL);
	i = 1;
	while(env[i])
	{
		ft_lstadd_back(&head, ft_lstnew(ft_strdup(env[i])));
		i++;
	}
	return (head);
}

void signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		sig_code = SIGINT;
		write (STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		sig_code = SIGQUIT;
		write (STDOUT_FILENO, "Quit (core dumped)\n", 19);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	setup_sig_handler()
{
	struct sigaction sa;
	struct sigaction ignore_sa;
	int i;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = signal_handler;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	i = -1;
	while(++i < _NSIG)
	{
		if (i == SIGKILL || i == SIGSTOP || i == SIGINT || i == SIGQUIT)
			continue;
		ft_memset(&ignore_sa, 0, sizeof(ignore_sa));
		ignore_sa.sa_handler = SIG_IGN;
		sigaction(i, &ignore_sa, NULL);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_mini	shell;

	(void)av;
	setup_sig_handler();
	shell.envp = envp;
	shell.env = init_env(envp);
	while(ac)
	{
		sig_code = 0;
		shell.input = readline("minishell$ ");
		if (!shell.input)
			ctrl_d_case(&shell);
		if (sig_code == SIGINT)
			sig_code = 0;
		else
			parsing(&shell);
	}
}
