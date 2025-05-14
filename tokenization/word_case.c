/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_case.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:44:03 by francema          #+#    #+#             */
/*   Updated: 2025/05/14 17:08:15 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*word_case(t_mini *shell, char *content, size_t *i)
{
	char	*s;
	char	*tmp;
	int		len;

	s = shell->input;
	len = ft_strlen_till_space(s, *i);
	tmp = ft_substr(s, *i, len);
	if (!tmp)
		return (NULL);
	content = ft_strjoin_free(content, tmp);
	free(tmp);
	if (!content)
		return (NULL);
	(*i) += len;
	return (content);
}
