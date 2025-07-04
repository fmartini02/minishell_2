/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_simple_cmd_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalloli <mdalloli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:05:30 by mdalloli          #+#    #+#             */
/*   Updated: 2025/07/01 12:13:57 by mdalloli         ###   ########.fr       */
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

char	**add_arg_to_array(char **args, char *new_arg)
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
		free(args[i]);
		i++;
	}
	new_args[i++] = ft_strdup(new_arg);
	new_args[i] = NULL;
	free(args);
	return (new_args);
}

t_cmd_info	*add_arg_to_cmd(t_cmd_info *cmd, char *arg)
{
	if (!cmd || !arg)
		return (cmd);
	cmd->cmd_args = add_arg_to_array(cmd->cmd_args, arg);
	return (cmd);
}

bool	handle_redirections(t_tok_lst **tokens, t_cmd_info *cmd, t_mini *shell)
{
	char	*token;

	if (!is_valid_token(tokens))
		return (true);
	if ((*tokens)->next && (*tokens)->next->type == DOLLAR
		&& (*tokens)->next->next && (*tokens)->next->next->type == DOLLAR)
	{
		write(2, "minishell: ", 12);
		write(2, (*tokens)->next->tok_name,
			ft_strlen((*tokens)->next->tok_name));
		write(2, ": ambiguous redirect\n", 22);
		return (false);
	}
	token = (*tokens)->content;
	if (!ft_strcmp(token, "<") || !ft_strcmp(token, ">")
		|| !ft_strcmp(token, ">>") || !ft_strcmp(token, "<<"))
	{
		if (parse_redirection(tokens, cmd, shell) == false)
			return (false);
	}
	return (true);
}
