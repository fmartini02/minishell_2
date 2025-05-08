/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <fmartini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 22:38:32 by fmartini          #+#    #+#             */
/*   Updated: 2024/01/27 22:38:32 by fmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "std_fun.h"
#include <stdio.h>

int	ft_len(long int n)
{
	int	len;

	len = 0;
	if (n < 0)
	{
		n *= -1;
		len++;
	}
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*limits_cases(int n)
{
	if (n == INT_MIN)
		return (ft_strdup("-2147483648"));
	else if (n == INT_MAX)
		return (ft_strdup("2147483647"));
	return (NULL);
}

void	ft_itoa_utils(int n, char *res, int flag)
{
	int	len;

	len = ft_len(n);
	res[len] = '\0';
	if (flag)
	{
		n *= -1;
		res[0] = '-';
	}
	len--;
	while (n != 0)
	{
		res[len] = (n % 10) + 48;
		n /= 10;
		len--;
	}
}

char	*ft_itoa(int n)
{
	char	*res;
	int		flag;

	if (n < 0)
		flag = 1;
	else
		flag = 0;
	if (n == INT_MIN || n == INT_MAX)
		return (limits_cases(n));
	else if (n == 0)
		return (ft_strdup("0"));
	else
	{
		res = malloc(ft_len(n) + 1);
		if (!res)
			return (NULL);
		ft_itoa_utils(n, res, flag);
	}
	return (res);
}
/*
int	main()
{
	char	*str;

	// str = ft_itoa(INT_MIN);
	// printf("%s\n", str);
	// free(str);
	// str = ft_itoa(INT_MAX);
	// printf("%s\n", str);
	// free(str);
	// str = ft_itoa(0);
	// printf("%s\n", str);
	// free(str);
	// str = ft_itoa(1234567890);
	// printf("%s\n", str);
	// free(str);
	str = ft_itoa(0);
	printf("%s", str);
	free(str);
	return (0);
}
*/
