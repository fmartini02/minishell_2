/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalloli <mdalloli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:12:36 by mdalloli          #+#    #+#             */
/*   Updated: 2025/06/25 16:12:58 by mdalloli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	env_list_count(t_list *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

static int	fill_env_array(char **envp, t_list *env)
{
	int	i;

	i = 0;
	while (env)
	{
		envp[i] = ft_strdup((char *)env->content);
		if (!envp[i])
			return (-1);
		env = env->next;
		i++;
	}
	envp[i] = NULL;
	return (0);
}

char	**env_list_to_array(t_list *env)
{
	char	**envp;
	int		count;

	count = env_list_count(env);
	envp = malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return (NULL);
	if (fill_env_array(envp, env) < 0)
	{
		free_split(envp);
		return (NULL);
	}
	return (envp);
}
