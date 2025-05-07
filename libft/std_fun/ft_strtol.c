/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:48:28 by francema          #+#    #+#             */
/*   Updated: 2025/05/07 17:06:13 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "std_fun.h"

static int	ft_base_detect(const char **str, int base)
{
	if ((base == 0 || base == 16) && str[0][0] == '0'
		&& (str[0][1] == 'x' || str[0][1] == 'X'))
	{
		*str += 2;
		return (16);
	}
	if (base == 0 && str[0][0] == '0')
	{
		(*str)++;
		return (8);
	}
	if (base == 0)
		return (10);
	return (base);
}

static int	ft_get_digit(char c)
{
	if (ft_isdigit((unsigned char)c))
		return (c - '0');
	if (ft_isalpha((unsigned char)c))
		return (ft_tolower((unsigned char)c) - 'a' + 10);
	return (-1);
}

static int	ft_sign(const char **str)
{
	if (**str == '-')
	{
		(*str)++;
		return (-1);
	}
	if (**str == '+')
		(*str)++;
	return (1);
}

long	ft_strtol(const char *nptr, char **endptr, int base)
{
	const char	*str = nptr;
	long		res;
	int			sign;
	int			d;

	res = 0;
	while (ft_ispace((int)*str))
		str++;
	sign = ft_sign(&str);
	base = ft_base_detect(&str, base);
	while (*str)
	{
		d = ft_get_digit(*str);
		if (d < 0 || d >= base)
			break;
		if (res > (LONG_MAX - d) / base)
			return (sign == 1 ? LONG_MAX : LONG_MIN);
		res = res * base + d;
		str++;
	}
	if (endptr)
		*endptr = (char *)str;
	return (res * sign);
}
