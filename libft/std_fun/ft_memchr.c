/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <fmartini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 23:17:11 by fmartini          #+#    #+#             */
/*   Updated: 2024/01/27 23:17:11 by fmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "std_fun.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t		i;
	void		*res;

	i = 0;
	res = (void *)s;
	while (i < n)
	{
		if (((unsigned char *)res)[i] == (unsigned char)c)
			return ((char *)s + i);
		i++;
	}
	return (0);
}
