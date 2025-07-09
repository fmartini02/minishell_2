/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 09:51:19 by francema          #+#    #+#             */
/*   Updated: 2025/07/08 18:10:35 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "std_fun.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char		*str;
	size_t		size;
	int			i;
	int			j;

	i = -1;
	j = 0;
	str = 0;
	if (!s1)
	{
		s1 = ft_strdup("");
		if (!s1)
			return (NULL);
	}
	size = ft_strlen(s2) + ft_strlen(s1) + 1;
	str = (char *)malloc(size);
	if (!str)
		return (NULL);
	while (++i < (int)ft_strlen(s1))
		str[i] = s1[i];
	while (j < (int)ft_strlen(s2))
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	return (str);
}
