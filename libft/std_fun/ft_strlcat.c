/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <fmartini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 22:43:15 by fmartini          #+#    #+#             */
/*   Updated: 2024/01/27 22:43:15 by fmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "std_fun.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	res;

	if (size <= ft_strlen(dst))
		res = size + ft_strlen(src);
	else
	{
		i = 0;
		j = ft_strlen(dst);
		while (src[i] && j + 1 < size)
		{
			dst[j] = src[i];
			i++;
			j++;
		}
		dst[j] = '\0';
		res = ft_strlen(dst) + ft_strlen(&src[i]);
	}
	return (res);
}
