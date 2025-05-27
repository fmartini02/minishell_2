/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_simple_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:55:06 by francema          #+#    #+#             */
/*   Updated: 2025/05/27 17:47:13 by francema         ###   ########.fr       */
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
		new_args[i] = args[i];
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

t_ast_node	*parse_simple_cmd(t_mini *shell, t_list **tokens)
{
	t_cmd_info	*cmd;
	t_ast_node	*node;
	char		*token;

	if (!tokens || !*tokens || !(*tokens)->content)
		return (NULL);
	if (!ft_strcmp((char *)(*tokens)->content, "(")
		|| !ft_strcmp((char *)(*tokens)->content, ")"))
		return (parse_subshell(shell, tokens));
	cmd = malloc(sizeof(t_cmd_info));
	if (!cmd)
		return (NULL);
	cmd->cmd_name = NULL;
	cmd->cmd_args = NULL;
	cmd->redirections = NULL;
	while (is_valid_token(tokens) && !is_control_operator((*tokens)->content))
	{
		token = (char *)(*tokens)->content;
		if (!ft_strcmp(token, "("))
		{
			ft_putendl_fd("minishell: syntax error near unexpected token `('", 2);
			free_cmd_info(cmd);
			return (NULL);
		}
		else
		{
			if (!cmd->cmd_name)
				cmd->cmd_name = ft_strdup(token);
			cmd = add_arg_to_cmd(cmd, token);
			*tokens = (*tokens)->next;
		}
	}
	if (is_valid_token(tokens))
		token = (char *)(*tokens)->content;
	if (!ft_strcmp(token, "<") || !ft_strcmp(token, ">")
		|| !ft_strcmp(token, ">>") || !ft_strcmp(token, "<<"))
	{
		if (parse_redirection(tokens, cmd) == false)
		{
			free_ast(shell->ast_root);
			return (NULL);
		}
	}
	if (!cmd->cmd_name)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		if (!is_valid_token(tokens))
			ft_putstr_fd("newline", 2);
		else
			ft_putstr_fd((char *)(*tokens)->content, 2);
		ft_putstr_fd("`\n", 2);
		free_cmd_info(cmd);
		return (NULL);
	}
	node = create_cmd_node(cmd);
	if (!node)
		return (free_cmd_info(cmd), NULL);
	return (node);
}
