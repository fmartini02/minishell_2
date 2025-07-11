/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast_stuff.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 23:28:42 by francema          #+#    #+#             */
/*   Updated: 2025/07/11 23:34:54 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_redirections(t_redirection *redir)
{
	t_redirection	*tmp;

	while (redir)
	{
		tmp = redir->next;
		free(redir->target);
		free(redir);
		redir = tmp;
	}
}

/*questa funzione viene chiamata se durante
la creazione della matrice degli argomenti qualcosa va storto*/
static char	**free_partial_array(char **arr, int last_index)
{
	while (--last_index >= 0)
		free(arr[last_index]);
	free(arr);
	return (NULL);
}

void	free_cmd_info(t_cmd_info *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return ;
	if (cmd->cmd_args)
	{
		while (cmd->cmd_args[i])
			free(cmd->cmd_args[i++]);
		free(cmd->cmd_args);
	}
	free(cmd->cmd_name);
	free_redirections(cmd->redirections);
	free(cmd);
	cmd = NULL;
}

void	free_ast(t_ast_node *node)
{
	if (!node)
		return ;
	if (node->type == NODE_CMD && node->content)
		free_cmd_info((t_cmd_info *)node->content);
	else if (node->type == NODE_SUBSHELL && node->content)
		free_ast((t_ast_node *)node->content);
	free_ast(node->left);
	free_ast(node->right);
	node->left = NULL;
	node->right = NULL;
	node->content = NULL;
	free(node);
}
