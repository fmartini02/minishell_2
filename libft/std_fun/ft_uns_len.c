/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uns_len.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:25:33 by francema          #+#    #+#             */
/*   Updated: 2025/04/30 13:57:45 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "std_fun.h"

int	ft_uns_len(unsigned long n, int base, int cast_type)
{
	int	len;

	len = 0;
	if (cast_type == 0)
		n = (unsigned int)n;
	else if (cast_type == 1)
		n = (unsigned long)n;
	else if (cast_type == 2)
		n = (unsigned long long)n;
	else if (cast_type == 3)
		n = (unsigned short)n;
	else if (cast_type == 4)
		n = (unsigned char)n;
	else if (cast_type == 5)
		n = (size_t)n;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		len++;
		n /= base;
	}
	return (len);
}
