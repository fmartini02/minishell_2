/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_case.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:58:42 by francema          #+#    #+#             */
/*   Updated: 2025/05/22 17:56:10 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*wildcard_case(t_mini *shell, char *content, size_t *i)
{
	char	*s;

	s = shell->input;
	while (s[*i] && s[*i] == '*')
		(*i)++;
	content = ft_strdup("*");
	if (!content)
		ft_fatal_memerr(shell);
	return (content);
}
