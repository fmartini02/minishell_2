/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:25:08 by francema          #+#    #+#             */
/*   Updated: 2025/06/30 18:19:29 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ast_init(t_mini *shell)
{
	t_tok_lst	*tmp;

	tmp = shell->tok_input;
	if (!shell || !shell->tok_input)
		return ;
	shell->ast_root = parse_cmd_line(shell, shell->tok_input);
	if (shell->err_print == true)
	{
		free_ast(shell->ast_root);
		shell->err_print = false;
	}
}
