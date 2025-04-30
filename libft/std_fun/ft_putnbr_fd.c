/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <fmartini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 22:41:53 by fmartini          #+#    #+#             */
/*   Updated: 2024/01/27 22:41:53 by fmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "std_fun.h"
#include <limits.h>

void	ft_putnbr_fd(int n, int fd)
{
	long int	nb;

	nb = n;
	if (fd < 0)
		return ;
	if (nb == INT_MIN)
	{
		ft_putchar_fd('-', fd);
		ft_putchar_fd('2', fd);
		nb = 147483648;
	}
	if (nb < 0)
	{
		ft_putchar_fd('-', fd);
		nb = -nb;
	}
	if (nb > 9)
	{
		ft_putnbr_fd(nb / 10, fd);
		nb = nb % 10;
	}
	if (nb < 10)
		ft_putchar_fd(nb + 48, fd);
}
/*
int	main()
{
	ft_putnbr_fd(-2147483648, -1);
	return (0);
}
*/
