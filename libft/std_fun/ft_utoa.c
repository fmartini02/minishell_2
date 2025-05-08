/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 18:35:41 by francema          #+#    #+#             */
/*   Updated: 2025/04/30 13:58:01 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "std_fun.h"

void	ft_utoa_utils(unsigned long long int n, char *res, int cast_type)
{
	int	len;

	len = ft_uns_len(n, 10, cast_type);
	res[len--] = '\0';
	while (n != 0)
	{
		res[len--] = (n % 10) + 48;
		n /= 10;
	}
}

char	*ft_utoa(unsigned long long int n, int cast_type)
{
	char	*s;

	if (n == 0)
		return (ft_strdup("0"));
	else
	{
		s = malloc(ft_uns_len(n, 10, cast_type) + 1);
		if (!s)
			return (NULL);
		ft_utoa_utils(n, s, cast_type);
	}
	return (s);
}
