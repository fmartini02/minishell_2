/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:19:20 by francema          #+#    #+#             */
/*   Updated: 2025/06/25 12:20:29 by mdalloli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Implementazone di env
Stampa le variabili d'ambiente presenti nella lista shell->env*/
void	ft_env(t_mini *shell, char **args)
{
	t_list	*tmp;

	(void)args;
	tmp = shell->env;
	ft_print_list(tmp, 's');
}
