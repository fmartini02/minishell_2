/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doll_expansion_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 22:31:42 by francema          #+#    #+#             */
/*   Updated: 2025/07/12 18:46:03 by francema         ###   ########.fr       */
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
