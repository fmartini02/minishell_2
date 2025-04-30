/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <fmartini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 22:43:59 by fmartini          #+#    #+#             */
/*   Updated: 2024/01/27 22:43:59 by fmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "std_fun.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		res;

	i = 0;
	if (n == 0)
	{
		res = 0;
	}
	else
	{
		while (s1[i] != '\0' && s1[i] == s2[i] && i < n - 1)
		{
			i++;
		}
		res = ((unsigned char)s1[i] - (unsigned char)s2[i]);
	}
	return (res);
}
