/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_simple_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:55:06 by francema          #+#    #+#             */
/*   Updated: 2025/06/30 14:18:49 by francema         ###   ########.fr       */
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

bool	simple_cmd_loop(t_mini *shell, t_tok_lst **tokens, t_cmd_info **cmd)
{
	char		*token;
	t_tok_lst	*tmp;

	tmp = *tokens;
	while (is_valid_token(&tmp) && !is_control_operator(tmp->content))
	{
		token = (char *)tmp->content;
		if (!ft_strcmp(token, "(") && shell->err_print == false)
		{
			shell->err_print = true;
			ft_putendl_fd("minishell: syntax error near unexpected token `('", 2);
			free_cmd_info(*cmd);
			return (false);
		}
		else
		{
			*cmd = add_arg_to_cmd(*cmd, token);
			if (!(*cmd)->cmd_name)
				(*cmd)->cmd_name = (*cmd)->cmd_args[0];
			tmp = tmp->next;
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

bool	is_parse_subshell(t_tok_lst**tokens)
{
	if (!is_valid_token(tokens))
		return (false);
	if (!ft_strcmp((char *)(*tokens)->content, "(")
		|| !ft_strcmp((char *)(*tokens)->content, ")"))
		return (true);
	return (false);
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
	token = (char *)(*tokens)->content;
	if (!ft_strcmp(token, "<") || !ft_strcmp(token, ">")
		|| !ft_strcmp(token, ">>") || !ft_strcmp(token, "<<"))
	{
		if (parse_redirection(tokens, cmd, shell) == false)
			return (false);
	}
	return (true);
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

t_ast_node	*parse_simple_cmd(t_mini *shell, t_tok_lst**tokens)
{
	t_cmd_info	*cmd;

	if (!is_valid_token(tokens))
		return (NULL);
	if (is_parse_subshell(tokens))
		return (parse_subshell(shell, tokens));
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
