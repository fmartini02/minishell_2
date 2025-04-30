/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:30:45 by francema          #+#    #+#             */
/*   Updated: 2025/04/30 18:33:08 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing(t_mini *shell)
{
	printf("%s\n", shell->input);
	free(shell->input);
}

void	ctrl_d_case(t_mini *shell)
{
	free(shell->input);
	ft_lstclear(shell->env);
	exit(0);
}

t_list	*init_env(char **env)
{
	t_list	*head;
	int		i;

	if (env[0])
		head = ft_lstnew((void *) env[0]);
	else
		return(NULL);
	i = 1;
	while(env[i])
	{
		ft_lstadd_back(&head, ft_lstnew(env[i]));
		i++;
	}
	return (head);
}

int	main(int ac, char **av, char **envp)
{
	t_mini	shell;

	(void)ac;
	(void)av;
	shell.envp = envp;
	shell.env = init_env(envp);
	ft_print_mat_str(shell.envp, 1);
	ft_printf("\n\nprint_list\n\n");
	ft_print_list(shell.env, 's');
	while(1)
	{
		shell.input = readline("minishell$ ");
		if (!shell.input)
			ctrl_d_case(&shell);
		else
			parsing(&shell);
	}
}
