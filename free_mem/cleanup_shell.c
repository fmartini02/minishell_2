/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 13:50:22 by mdalloli          #+#    #+#             */
/*   Updated: 2025/07/11 23:35:54 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_ast_tok_unit_input_prompt(t_mini *shell)
{
	if (shell->ast_root)
	{
		free_ast(shell->ast_root);
		shell->ast_root = NULL;
	}
	if (shell->tok_input)
	{
		free_tok_lst(shell->tok_input);
		shell->tok_input = NULL;
	}
	if (shell->unit)
	{
		free_exec_unit(shell->unit);
		shell->unit = NULL;
	}
	if (shell->input)
	{
		free(shell->input);
		shell->input = NULL;
	}
	if (shell->prompt)
	{
		free(shell->prompt);
		shell->prompt = NULL;
	}
}

void	cleanup_shell(t_mini *shell, int exit_code)
{
	if (!shell)
		exit(exit_code);
	if (exit_code >= 0)
		free_env(shell);
	free_ast_tok_unit_input_prompt(shell);
	if (shell->err_print == true)
		shell->last_exit_code = 2;
	if (exit_code >= 0)
		exit(exit_code);
}
