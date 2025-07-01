/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:19:01 by francema          #+#    #+#             */
/*   Updated: 2025/07/01 10:45:33 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Implementazione di pwd
Stampa la directory corrente*/
void	ft_pwd(t_mini *shell, char **args)
{
	char	*pwd;

	(void)shell;
	(void)args;
	pwd = malloc(PATH_MAX);
	if (!pwd)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	if (!getcwd(pwd, PATH_MAX))
	{
		perror("getcwd");
		free(pwd);
		exit(EXIT_FAILURE);
	}
	ft_printf("%s\n", pwd);
	free(pwd);
	cleanup_shell(shell, -1);
	ft_lstclear(&shell->env, free);
}
