/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:52:18 by francema          #+#    #+#             */
/*   Updated: 2025/05/21 17:53:45 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Helper function to create a new redirection node
static t_redirection	*new_redirection(t_redir_type type, char *target)
{
	t_redirection	*redir;

	redir = malloc(sizeof(t_redirection));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->target = strdup(target);
	if (!redir->target)
	{
		free(redir);
		return (NULL);
	}
	redir->next = NULL;
	return (redir);
}

static int	add_redirection(t_cmd_info *cmd, t_redirection *new_redir)
{
	t_redirection	*curr;

	if (!cmd || !new_redir)
		return (-1);
	if (!cmd->redirections)
	{
		cmd->redirections = new_redir;
		return (0);
	}
	curr = cmd->redirections;
	while (curr->next)
		curr = curr->next;
	curr->next = new_redir;
	return (0);
}

// Adds a redirection to the end of the list, returns 0 on success, -1 on failure
void	parse_redirection(t_list **tokens, t_cmd_info *cmd)
{
	t_redirection	*redir;
	t_redir_type	type;
	char		*token;

	while (*tokens && (*tokens)->content)
	{
		token = (char *)(*tokens)->content;
		if (ft_strcmp(token, "<") == 0)
			type = REDIR_INPUT;
		else if (ft_strcmp(token, ">") == 0)
			type = REDIR_OUTPUT;
		else if (ft_strcmp(token, ">>") == 0)
			type = REDIR_APPEND;
		else if (ft_strcmp(token, "<<") == 0)
			type = REDIR_HEREDOC;
		else
			break;
		*tokens = (*tokens)->next;
		if (!*tokens || !(*tokens)->content)
		{
			ft_putendl_fd("minishell: syntax error near unexpected token `newline`", 2);
			free_redirections(cmd->redirections);
			cmd->redirections = NULL;
			return;
		}
		redir = new_redirection(type, (char *)(*tokens)->content);
		if (!redir || add_redirection(cmd, redir) == -1)
		{
			free_redirections(cmd->redirections);
			cmd->redirections = NULL;
			if (redir)
				free(redir);
			return;
		}
		*tokens = (*tokens)->next;
	}
}
