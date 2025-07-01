/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalloli <mdalloli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:55:00 by francema          #+#    #+#             */
/*   Updated: 2025/07/01 14:18:31 by mdalloli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_indent(int depth, int is_last)
{
	int	i;

	i = 0;
	while (i < depth - 1)
	{
		printf("│   ");
		i++;
	}
	if (depth > 0)
	{
		if (is_last)
			printf("└── ");
		else
			printf("├── ");
	}
}

static void	print_redirections(t_redirection *redir, int depth)
{
	while (redir)
	{
		print_indent(depth, 1);
		if (redir->type == REDIR_INPUT)
			printf("< %s\n", redir->target);
		else if (redir->type == REDIR_OUTPUT)
			printf("> %s\n", redir->target);
		else if (redir->type == REDIR_APPEND)
			printf(">> %s\n", redir->target);
		else if (redir->type == REDIR_HEREDOC)
			printf("<< %s\n", redir->target);
		redir = redir->next;
	}
}

static void	print_cmd(t_cmd_info *cmd, int depth)
{
	int	i;

	printf("COMMAND: ");
	if (cmd->cmd_name)
		printf("%s\n", cmd->cmd_name);
	else
		printf("(null)\n");
	i = 0;
	while (cmd->cmd_args && cmd->cmd_args[i])
	{
		print_indent(depth, 0);
		printf("arg[%d]: %s\n", i, cmd->cmd_args[i]);
		i++;
	}
	if (cmd->redirections)
	{
		print_indent(depth, 0);
		printf("Redirections:\n");
		print_redirections(cmd->redirections, depth + 1);
	}
}

static void	print_logical_nodes(t_ast_node *node, int depth)
{
	print_indent(depth, 1);
	if (node->type == NODE_PIPELINE)
		printf("PIPELINE (|)\n");
	else if (node->type == NODE_AND)
		printf("AND (&&)\n");
	else if (node->type == NODE_OR)
		printf("OR (||)\n");
	else if (node->type == NODE_SUBSHELL)
	{
		printf("SUBSHELL\n");
		print_ast((t_ast_node *)node->content, depth + 1);
		return ;
	}
}

void	print_ast(t_ast_node *node, int depth)
{
	if (!node)
		return ;
	if (node->type == NODE_CMD)
	{
		print_indent(depth, 1);
		print_cmd((t_cmd_info *)node->content, depth + 1);
	}
	else
		print_logical_nodes(node, depth);
	if (node->left)
	{
		print_indent(depth + 1, 0);
		printf("Left:\n");
		print_ast(node->left, depth + 2);
	}
	if (node->right)
	{
		print_indent(depth + 1, 1);
		printf("Right:\n");
		print_ast(node->right, depth + 2);
	}
}
