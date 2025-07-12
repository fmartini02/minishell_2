/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_var_name.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 14:02:23 by francema          #+#    #+#             */
/*   Updated: 2025/07/12 15:39:54 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Handles the special case $?
Returns the string containing the value of last_exit_code */
static char	*expand_exit_code(t_mini *shell, size_t *i)
{
	char	*value;
	char	*result;

	value = ft_itoa(shell->last_exit_code);
	if (!value)
		ft_fatal_memerr(shell);
	result = ft_strdup(value);
	free(value);
	*i += 2;
	return (result);
}

char	*handle_special_dollar_cases(t_mini *shell, char *str, size_t *i)
{
	if (str[*i + 1] == '?')
		return (expand_exit_code(shell, i));
	if (str[*i + 1] >= '0' && str[*i + 1] <= '9')
		return ((*i) += 2, ft_strdup(""));
	return (NULL);
}

/* Extracts the variable name from a string after the symbol '$' */
char	*extract_var_name(char *str, size_t start, size_t *end)
{
	size_t	j;

	j = start;
	while (str[j] && !ft_ispecial_char(str[j]) && str[j] != ' ')
		j++;
	*end = j;
	return (ft_substr(str, start, j - start));
}
