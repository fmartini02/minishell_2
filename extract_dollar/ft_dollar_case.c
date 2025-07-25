/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dollar_case.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 23:40:12 by francema          #+#    #+#             */
/*   Updated: 2025/07/12 14:44:56 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*handle_env_lookup_result(
	t_mini *shell, char *var_name, char *var_value)
{
	char	*ret;

	if (!var_value)
	{
		free(var_name);
		ret = ft_strdup("");
		if (!ret)
			ft_fatal_memerr(shell);
		return (ret);
	}
	ret = ft_strdup(var_value);
	if (!ret)
		ft_fatal_memerr(shell);
	free(var_name);
	return (ret);
}

/* Restitutes the value associated with an environment variable */
char	*get_env_value(t_mini *shell, const char *var_name)
{
	t_list	*env_list;
	char	*entry;
	size_t	key_len;

	env_list = shell->env;
	key_len = ft_strlen(var_name);
	while (env_list)
	{
		entry = (char *)env_list->content;
		if (ft_strncmp(entry, var_name, key_len) == 0 && entry[key_len] == '=')
			return (entry + key_len + 1);
		env_list = env_list->next;
	}
	return (NULL);
}

char	*ft_dollar_case(t_mini *shell, char *str, size_t *i)
{
	size_t	start;
	size_t	j;
	char	*var_name;
	char	*var_value;
	char	*ret;

	start = *i + 1;
	ret = handle_special_dollar_cases(shell, str, i);
	if (ret)
		return (ret);
	var_name = extract_var_name(str, start, &j);
	if (!var_name)
		return (*i = j, NULL);
	var_value = get_env_value(shell, var_name);
	*i = j;
	return (handle_env_lookup_result(shell, var_name, var_value));
}
