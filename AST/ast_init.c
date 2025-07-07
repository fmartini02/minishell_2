/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:25:08 by francema          #+#    #+#             */
/*   Updated: 2025/07/07 22:07:47 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ast_init(t_mini *shell)
{
	if (!shell || !shell->tok_input)
		return ;
	shell->ast_root = parse_cmd_line(shell, &shell->tok_input);
}
