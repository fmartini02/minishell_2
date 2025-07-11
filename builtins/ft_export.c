/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:20:58 by mdalloli          #+#    #+#             */
/*   Updated: 2025/07/12 00:07:03 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	var_exists(t_list *env, const char *key)
{
	size_t	len;

	len = ft_strlen(key);
	while (env)
	{
		if (ft_strncmp(env->content, key, len) == 0
			&& (((char *)env->content)[len] == '\0'
			|| ((char *)env->content)[len] == '='))
			return (1);
		env = env->next;
	}
	return (0);
}

static int	is_valid_varname(const char *name)
{
	int	i;

	if (!name || !*name)
		return (0);
	if (!(ft_isalpha(name[0]) || name[0] == '_'))
		return (0);
	i = 1;
	while (name[i] && name[i] != '=')
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

/* Aggiorna il valore di una variabile esistente o la aggiunge se non esiste*/
static void	update_env_var(t_list **env, const char *key, const char *value)
{
	t_list	*node;
	size_t	key_len;
	char	*tmp;
	char	*new_var;

	key_len = ft_strlen(key);
	node = *env;
	while (node)
	{
		if (ft_strncmp(node->content, key, key_len) == 0
			&& ((char *)node->content)[key_len] == '=')
		{
			free(node->content);
			new_var = ft_strjoin(key, "=");
			tmp = ft_strjoin(new_var, value);
			free(new_var);
			node->content = tmp;
			return ;
		}
		node = node->next;
	}
	new_var = ft_strjoin(key, "=");
	tmp = ft_strjoin(new_var, value);
	free(new_var);
	ft_lstadd_back(env, ft_lstnew(tmp));
}

void	export_err(char *s)
{
	ft_putstr_fd("minishell: export: ", STDERR_FILENO);
	ft_putstr_fd(s, STDERR_FILENO);
	ft_putendl_fd(": not a valid identifier", STDERR_FILENO);
}

void	ft_export(t_mini *shell, char **args)
{
	int		i;
	char	*eq;

	if (!args[1])
		return (print_sorted_env(shell->env));
	i = 1;
	while (args[i])
	{
		eq = ft_strchr(args[i], '=');
		if (eq)
		{
			*eq = '\0';
			if (is_valid_varname(args[i]))
				update_env_var(&shell->env, args[i], eq + 1);
			else
				export_err(args[i]);
			*eq = '=';
		}
		else if (!is_valid_varname(args[i]))
			export_err(args[i]);
		else if (!var_exists(shell->env, args[i]))
			ft_lstadd_back(&shell->env, ft_lstnew(ft_strdup(args[i])));
		i++;
	}
}
