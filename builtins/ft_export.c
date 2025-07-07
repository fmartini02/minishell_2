/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:20:58 by mdalloli          #+#    #+#             */
/*   Updated: 2025/07/07 11:06:37 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			node->content = ft_strjoin(key, "=");
			tmp = ft_strjoin(node->content, value);
			free(node->content);
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

static void	print_export_line(char *str)
{
	char	*eq;

	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	eq = ft_strchr(str, '=');
	if (eq)
	{
		*eq = '\0';
		ft_putstr_fd(str, STDOUT_FILENO);
		ft_putstr_fd("=\"", STDOUT_FILENO);
		ft_putstr_fd(eq + 1, STDOUT_FILENO);
		ft_putendl_fd("\"", STDOUT_FILENO);
		*eq = '=';
	}
	else
		ft_putendl_fd(str, STDOUT_FILENO);
}

static void	print_sorted_env(t_list *env)
{
	char	**env_array;
	int		i;

	env_array = env_list_to_array(env);
	if (!env_array)
		return ;
	ft_sort_strarr(env_array);
	i = 0;
	while (env_array[i])
		print_export_line(env_array[i++]);
	free_split(env_array);
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
				ft_putendl_fd("minishell: export: not a valid identifier", 2);
			*eq = '=';
		}
		else if (!is_valid_varname(args[i]))
			ft_putendl_fd("minishell: export: not a valid identifier", 2);
		else
			ft_lstadd_back(&shell->env, ft_lstnew(args[i]));
		i++;
	}
}
