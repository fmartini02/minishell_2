/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:19:20 by francema          #+#    #+#             */
/*   Updated: 2025/05/20 15:55:42 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Implementazone di env
Stampa le variabili d'ambiente presenti nella lista shell->env*/
void	ft_env(t_mini *shell, char **args)
{
	(void)args;
	t_list	*tmp = shell->env;
	ft_print_list(tmp, 's');
}


