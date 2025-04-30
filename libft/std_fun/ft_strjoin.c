/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <fmartini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 22:43:06 by fmartini          #+#    #+#             */
/*   Updated: 2024/01/27 22:43:06 by fmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "std_fun.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	lens1;
	size_t	lens2;
	char	*res;

	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	res = malloc(sizeof(char) * (lens1 + lens2) + 1);
	if (!res)
		return (NULL);
	ft_memcpy(res, s1, lens1);
	ft_memcpy(&res[lens1], s2, lens2);
	res[lens1 + lens2] = '\0';
	return (res);
}
