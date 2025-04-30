/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <fmartini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 22:45:01 by fmartini          #+#    #+#             */
/*   Updated: 2024/01/27 22:45:01 by fmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "std_fun.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	true_len;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	true_len = ft_strlen(s + start);
	if (true_len > len)
		true_len = len;
	sub = malloc(sizeof(char) * (true_len + 1));
	if (!sub)
		return (NULL);
	i = 0;
	while (i < true_len)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}
