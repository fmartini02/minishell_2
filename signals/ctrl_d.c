/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalloli <mdalloli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:56:38 by francema          #+#    #+#             */
/*   Updated: 2025/06/26 17:13:01 by mdalloli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Gestisce la fine dell'input (utente preme ctrl+D), libera la memoria ed esce*/
void	ctrl_d_case(t_mini *shell)
{
	free(shell->input);
	ft_lstclear(&shell->env, free);
	exit(0);
}
