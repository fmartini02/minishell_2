/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalloli <mdalloli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 13:50:22 by mdalloli          #+#    #+#             */
/*   Updated: 2025/07/01 14:04:17 by mdalloli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cleanup_env(t_mini *shell)
{
	if (shell->env)
	{
		ft_lstclear(&shell->env, free);
		shell->env = NULL;
	}
}

static void	cleanup_ast_and_tokens_and_unit(t_mini *shell)
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
}

static void	cleanup_cmd_and_input(t_mini *shell)
{
	if (shell->cmd_info)
	{
		free_cmd_info(shell->cmd_info);
		shell->cmd_info = NULL;
	}
	if (shell->input)
	{
		free(shell->input);
		shell->input = NULL;
	}
}

static void	cleanup_prompt_and_exit(t_mini *shell, int exit_code)
{
	if (shell->prompt)
	{
		free(shell->prompt);
		shell->prompt = NULL;
	}
	if (exit_code >= 0)
		exit(exit_code);
}

void	cleanup_shell(t_mini *shell, int exit_code)
{
	if (!shell)
		exit(exit_code);
	if (exit_code >= 0)
		cleanup_env(shell);
	cleanup_ast_and_tokens_and_unit(shell);
	cleanup_cmd_and_input(shell);
	cleanup_prompt_and_exit(shell, exit_code);
}
