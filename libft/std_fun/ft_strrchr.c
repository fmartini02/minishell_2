/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <fmartini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 22:44:44 by fmartini          #+#    #+#             */
/*   Updated: 2024/01/27 22:44:44 by fmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "std_fun.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*res;

	i = ft_strlen(s);
	while (i > 0 && s[i] != (unsigned char)c)
	{
		i--;
	}
	if (s[i] == (unsigned char)c)
		res = (char *)s + i;
	else
		res = 0;
	return (res);
}
