/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redi_case.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:38:41 by francema          #+#    #+#             */
/*   Updated: 2025/05/22 17:59:30 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*redi_case(t_mini *shell, char *content, size_t *i)
{
	char	*s;

	s = shell->input;
	if (s[*i] == '<')
	{
		if (s[*i + 1] == '<')
			content = ft_strdup("<<");
		else
			content = ft_strdup("<");
	}
	else if (s[*i] == '>')
	{
		if (s[*i + 1] == '>')
			content = ft_strdup(">>");
		else
			content = ft_strdup(">");
	}
	if (!content)
		ft_fatal_memerr(shell);
	*i += ft_strlen(content);
	return (content);
}
