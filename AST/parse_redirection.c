/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:52:18 by francema          #+#    #+#             */
/*   Updated: 2025/07/22 10:51:39 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Helper function to create a direction node
static t_redirection	*new_redi(t_redir_type type, t_tok_lst **tokens)
{
	t_redirection	*redir;

	redir = malloc(sizeof(t_redirection));
	if (!redir)
		return (NULL);
	redir->type = type;
	if (is_operator(tokens))
		return (free(redir), NULL);
	if ((*tokens)->type == SINGLE_QUOTES || (*tokens)->type == DOUBLE_QUOTES)
		redir->flag_here_doc = true;
	else
		redir->flag_here_doc = false;
	redir->target = strdup((*tokens)->content);
	if (!redir->target)
		return (free(redir), NULL);
	redir->heredoc_fd = -1;
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

t_redir_type	get_redir_type(char *token)
{
	if (ft_strcmp(token, "<") == 0)
		return (REDIR_INPUT);
	else if (ft_strcmp(token, ">") == 0)
		return (REDIR_OUTPUT);
	else if (ft_strcmp(token, ">>") == 0)
		return (REDIR_APPEND);
	else if (ft_strcmp(token, "<<") == 0)
		return (REDIR_HEREDOC);
	return (-1);
}

bool	parse_redi_utils(t_mini *shell, t_cmd_info *cmd)
{
	shell->err_print = true;
	ft_putendl_fd("minishell: syntax error near unexpected token `newline`", 2);
	free_redirections(cmd->redirections);
	cmd->redirections = NULL;
	return (false);
}

/* Adds a redirection to the end of the list, returns 0 on success,
-1 on failure */
bool	parse_redirection(t_tok_lst **tokens, t_cmd_info *cmd, t_mini *shell)
{
	t_redirection	*redir;
	t_redir_type	type;

	while (is_valid_token(tokens))
	{
		type = get_redir_type((*tokens)->content);
		if ((int)type == -1)
			break ;
		*tokens = (*tokens)->next;
		if (!is_valid_token(tokens) && shell->err_print == false)
			return (parse_redi_utils(shell, cmd));
		redir = new_redi(type, tokens);
		if (!redir || add_redirection(cmd, redir) == -1)
		{
			print_unexpected_token(tokens);
			free_redirections(cmd->redirections);
			cmd->redirections = NULL;
			if (redir)
				free(redir);
			return (shell->err_print = true, false);
		}
		*tokens = (*tokens)->next;
	}
	return (true);
}
