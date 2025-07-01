/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_simple_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalloli <mdalloli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:55:06 by francema          #+#    #+#             */
/*   Updated: 2025/07/01 12:13:41 by mdalloli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_ast_node	*create_cmd_node(t_cmd_info *cmd)
{
	t_ast_node	*node;

	if (!cmd)
		return (NULL);
	node = malloc(sizeof(t_ast_node));
	if (!node)
	{
		write(2, "minishell: malloc failed in create_cmd_node\n", 45);
		free_cmd_info(cmd);
		return (NULL);
	}
	node->type = NODE_CMD;
	node->content = cmd;
	node->left = NULL;
	node->right = NULL;
	node->next = NULL;
	return (node);
}

bool	simple_cmd_loop(t_mini *shell, t_tok_lst **tokens, t_cmd_info **cmd)
{
	char	*token;

	while (is_valid_token(tokens) && !is_control_operator(((*tokens)->content)))
	{
		token = (*tokens)->content;
		if (!ft_strcmp(token, "(") && shell->err_print == false)
		{
			shell->err_print = true;
			ft_putendl_fd("minishell: syntax error near unexpected token `('",
				2);
			free_cmd_info(*cmd);
			return (false);
		}
		else
		{
			*cmd = add_arg_to_cmd(*cmd, token);
			if (!(*cmd)->cmd_name)
				(*cmd)->cmd_name = (*cmd)->cmd_args[0];
			if (!(*tokens)->next)
				break ;
			*tokens = (*tokens)->next;
		}
	}
	return (true);
}

t_cmd_info	*create_cmd_info(void)
{
	t_cmd_info	*cmd;

	cmd = malloc(sizeof(t_cmd_info));
	if (!cmd)
		return (NULL);
	cmd->cmd_name = NULL;
	cmd->cmd_args = NULL;
	cmd->redirections = NULL;
	return (cmd);
}

t_ast_node	*finalize_cmd_node(t_cmd_info *cmd, t_mini *shell,
	t_tok_lst **tokens)
{
	t_ast_node	*node;

	if (!cmd->cmd_name && shell->err_print == false && !cmd->redirections)
	{
		shell->err_print = true;
		print_unexpected_token(tokens);
		free_cmd_info(cmd);
		return (NULL);
	}
	node = create_cmd_node(cmd);
	if (!node)
		return (free_cmd_info(cmd), NULL);
	return (node);
}

t_ast_node	*parse_simple_cmd(t_mini *shell, t_tok_lst **tokens)
{
	t_cmd_info	*cmd;

	if (!is_valid_token(tokens))
		return (NULL);
	cmd = create_cmd_info();
	if (!cmd)
		return (NULL);
	if (ft_strchr((*tokens)->content, '>')
		|| ft_strchr((*tokens)->content, '<'))
	{
		if (!handle_redirections(tokens, cmd, shell))
			return (free_ast(shell->ast_root), NULL);
	}
	if (!simple_cmd_loop(shell, tokens, &cmd))
		return (NULL);
	if (!handle_redirections(tokens, cmd, shell))
		return (free_ast(shell->ast_root), NULL);
	return (finalize_cmd_node(cmd, shell, tokens));
}
