/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <fmartini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 22:44:54 by fmartini          #+#    #+#             */
/*   Updated: 2024/01/27 22:44:54 by fmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "std_fun.h"
#include <stdio.h>

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	while (ft_strchr(set, s1[i]))
		i++;
	j = ft_strlen(s1);
	j--;
	while (ft_strchr(set, s1[j]))
		j--;
	res = ft_substr(s1, i, (j + 1) - i);
	return (res);
}
/*
int	main()
{
	printf("%s", ft_strtrim("   hcsvcs", NULL));
}*/
