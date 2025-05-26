/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:25:08 by francema          #+#    #+#             */
/*   Updated: 2025/05/22 17:51:09 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ast_init(t_mini *shell)
{
	if (!shell || !shell->tok_input)
		return;
	shell->ast_root = parse_cmd_line(shell, &(shell->tok_input));
	if (shell->tok_input != NULL)
	{
		write(2, "minishell: syntax error near unexpected token `", 48);
		if ((shell->tok_input)->content)
			ft_putstr_fd((char *)(shell->tok_input)->content, 2);
		else
			ft_putstr_fd("newline", 2);
		write(2, "'\n", 2);
		free_ast(shell->ast_root);
	}
	/*if (!shell->ast_root)
	{
		ft_putendl_fd("minishell: syntax error", 2);
	}*/
}

