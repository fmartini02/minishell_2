/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 10:02:48 by francema          #+#    #+#             */
/*   Updated: 2025/04/30 13:57:22 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "std_fun.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*str;
	size_t	i;

	if (!str)
		return (NULL);
	i = 0;
	str = malloc(sizeof(char) * (n + 1));
	while (s[i] && i < n)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
