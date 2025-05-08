/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_word_len.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:08:37 by francema          #+#    #+#             */
/*   Updated: 2025/05/08 15:21:18 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_word_len(char *s)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	if (!s)
		return(0);
	i = ft_skip_spaces(s, i);
	while(s[i] && !ft_ispace(s[i]))
	{
		len++;
		i++;
	}
	return (len);
}
