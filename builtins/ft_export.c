/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalloli <mdalloli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:20:58 by mdalloli          #+#    #+#             */
/*   Updated: 2025/06/26 15:57:34 by mdalloli         ###   ########.fr       */
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

// DA CONTROLLARE SE IGNORA TUTTI GLI UGUALI O SOLO IL PRIMO!!!!
/* Aggiunge o aggiorna una varibile d'ambiente nella lista shell->env*/
void	ft_export(t_mini *shell, char **args)
{
	int		i;
	char	*eq;

	i = 1;
	while (args && args[i])
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
		i++;
	}
}
