/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 00:06:41 by francema          #+#    #+#             */
/*   Updated: 2025/07/12 00:07:40 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	free_mat(env_array);
}
