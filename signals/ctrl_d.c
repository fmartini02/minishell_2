/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:56:38 by francema          #+#    #+#             */
/*   Updated: 2025/06/30 12:05:45 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Gestisce la fine dell'input (utente preme ctrl+D),
libera la memoria ed esce*/
void	ctrl_d_case(t_mini *shell)
{
	if (shell->envp)
		ft_lstclear(&shell->env, free);
	if (shell->ast_root)
		free_ast(shell->ast_root);
	if (shell->tok_input)
		free_tok_lst(shell->tok_input);
	if (shell->input)
		free(shell->input);
	exit(0);
}
