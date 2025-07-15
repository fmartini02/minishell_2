/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:21:33 by mdalloli          #+#    #+#             */
/*   Updated: 2025/07/15 15:53:24 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Rimuove una variabile d'ambiente dalla lista */
static void	remove_env_var(t_list **env, const char *key)
{
	t_list	*curr;
	t_list	*prev;
	t_list	*tmp;
	size_t	key_len;

	curr = *env;
	prev = NULL;
	key_len = ft_strlen(key);
	while (curr)
	{
		if (ft_strncmp(curr->content, key, key_len) == 0
			&& (((char *)curr->content)[key_len] == '\0'
			|| ((char *)curr->content)[key_len] == '='))
		{
			tmp = curr->next;
			if (prev)
				prev->next = tmp;
			else
				*env = tmp;
			return (free(curr->content), free(curr));
		}
		prev = curr;
		curr = curr->next;
	}
}

/* Rimuove una o piu' variabili d'ambiente dalla lista shell->env*/
void	ft_unset(t_mini *shell, char **args)
{
	int		i;

	i = 1;
	while (args && args[i])
	{
		remove_env_var(&shell->env, args[i]);
		i++;
	}
}
