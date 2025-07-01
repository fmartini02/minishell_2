/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:19:54 by francema          #+#    #+#             */
/*   Updated: 2025/07/01 16:40:26 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Controlla se c'è la flag -n attiva (per echo)*/
static bool	is_n_option(const char *str)
{
	int	i;

	i = 2;
	if (!str || str[0] != '-' || str[1] != 'n')
		return (false);
	while (str[i])
	{
		if (str[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

/* Implementazione di echo
Stampa gli argomenti passati separati da spazi,
se viene specificata l'opzione -n (o più meno -nn)
il carattere new_line non viene stampato*/
void	ft_echo(char **args, t_mini *shell)
{
	int		i;
	bool	new_line;

	i = 1;
	new_line = true;
	while (args[i] && is_n_option(args[i]))
	{
		new_line = false;
		i++;
	}
	while (args[i])
	{
		write(1, args[i], ft_strlen(args[i]));
		if (args[i + 1])
			ft_printf(" ");
		i++;
	}
	if (new_line)
		ft_printf("\n");
	shell->last_exit_code = 0;
	cleanup_shell(shell, -1);
	ft_lstclear(&shell->env, free);
}
