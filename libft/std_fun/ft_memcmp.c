/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <fmartini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 22:40:29 by fmartini          #+#    #+#             */
/*   Updated: 2024/01/27 22:40:29 by fmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "std_fun.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int		res;
	int		t;
	size_t	i;

	t = 0;
	res = 0;
	i = 0;
	while (i < n && !t)
	{
		if (((unsigned char *)s1)[i] < ((unsigned char *)s2)[i])
		{
			res = -1;
			t++;
		}
		else if (((unsigned char *)s1)[i] > ((unsigned char *)s2)[i])
		{
			res = 1;
			t++;
		}
		i++;
	}
	return (res);
}
