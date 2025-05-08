/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <fmartini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 22:44:09 by fmartini          #+#    #+#             */
/*   Updated: 2024/01/27 22:44:09 by fmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "std_fun.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*res;
	size_t	i;
	size_t	j;

	res = 0;
	i = 0;
	j = 0;
	if (little[0] == '\0')
		res = (char *)big;
	else
	{
		while (big[i] && little[j] != '\0' && (i + j) < len)
		{
			if (big[i + j] == little[j])
				j++;
			else
			{
				j = 0;
				i++;
			}
		}
		if (little[j] == '\0')
			res = (char *)&big[i];
	}
	return (res);
}
