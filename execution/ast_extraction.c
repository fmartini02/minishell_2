/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extraction.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:22:43 by mdalloli          #+#    #+#             */
/*   Updated: 2025/07/11 22:59:23 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**dup_argv(char **cmd_args, int argc)
{
	char	**argv;
	int		i;

	argv = malloc(sizeof(char *) * (argc + 1));
	if (!argv)
		return (NULL);
	i = 0;
	while (i < argc)
	{
		argv[i] = ft_strdup(cmd_args[i]);
		if (!argv[i])
		{
			while (--i >= 0)
				free(argv[i]);
			free(argv);
			return (NULL);
		}
		i++;
	}
	argv[argc] = NULL;
	return (argv);
}

/* Extracts execution unit from a command AST node */
t_exec_unit	*extract_exec_units(t_ast_node *node)
{
	t_cmd_info	*cmd;
	t_exec_unit	*unit;
	int			argc;

	if (!node || node->type != NODE_CMD)
		return (NULL);
	cmd = (t_cmd_info *)node->content;
	if ((!cmd || (!cmd->cmd_args || !cmd->cmd_args[0])) && !cmd->redirections)
		return (NULL);
	unit = malloc(sizeof(t_exec_unit));
	if (!unit)
		return (NULL);
	argc = 0;
	if (cmd->cmd_args)
	{
		while (cmd->cmd_args[argc])
			argc++;
		unit->argv = dup_argv(cmd->cmd_args, argc);
	}
	else
		unit->argv = NULL;
	unit->redirs = cmd->redirections;
	return (unit);
}
