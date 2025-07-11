/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_simple_cmd_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:05:30 by mdalloli          #+#    #+#             */
/*   Updated: 2025/07/11 23:55:19 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_parse_subshell(t_tok_lst **tokens)
{
	if (!is_valid_token(tokens))
		return (false);
	if (!ft_strcmp((*tokens)->content, "(")
		|| !ft_strcmp((*tokens)->content, ")"))
		return (true);
	return (false);
}

char	**add_arg_to_array(char **args, char *tok_str)
{
	char	**new_args;
	int		len;
	int		i;

	len = 0;
	len = ft_matlen((void **)args);
	new_args = malloc(sizeof(char *) * (len + 2));
	if (!new_args)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_args[i] = ft_strdup(args[i]);
		if (!new_args[i])
			return (free_partial_array(new_args, i), NULL);
		free(args[i]);
		i++;
	}
	new_args[i] = ft_strdup(tok_str);
	if (!new_args[i])
		return (free_partial_array(new_args, i));
	new_args[i + 1] = NULL;
	free(args);
	return (new_args);
}

t_cmd_info	*add_arg_to_cmd(t_cmd_info *cmd, char *tok_str)
{
	if (!cmd || !tok_str)
		return (cmd);
	cmd->cmd_args = add_arg_to_array(cmd->cmd_args, tok_str);
	return (cmd);
}

bool	handle_redirections(t_tok_lst **tokens, t_cmd_info *cmd, t_mini *shell)
{
	char	*token;

	if (!is_valid_token(tokens))
		return (true);
	token = (*tokens)->content;
	if (!ft_strcmp(token, "<") || !ft_strcmp(token, ">")
		|| !ft_strcmp(token, ">>") || !ft_strcmp(token, "<<"))
	{
		if (parse_redirection(tokens, cmd, shell) == false)
			return (false);
	}
	return (true);
}
