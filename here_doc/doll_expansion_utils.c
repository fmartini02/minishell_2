/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doll_expansion_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 22:31:42 by francema          #+#    #+#             */
/*   Updated: 2025/07/12 15:43:17 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	append_substr(
	char **to_print, char *line, size_t start, size_t end)
{
	char	*tmp;

	tmp = ft_substr(line, start, end - start);
	if (!tmp)
	{
		*to_print = NULL;
		return ;
	}
	*to_print = ft_strjoin_free(*to_print, tmp);
	if (tmp)
		free(tmp);
}

char	*append_var(char *line, size_t *i, char *to_print, t_mini *shell)
{
	char	*tmp;

	tmp = ft_dollar_case(shell, line, i);
	if (!tmp)
		ft_fatal_memerr(shell);
	to_print = ft_strjoin_free(to_print, tmp);
	free(tmp);
	return (to_print);
}
