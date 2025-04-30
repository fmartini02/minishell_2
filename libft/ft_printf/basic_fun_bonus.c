/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_fun_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:39:25 by francema          #+#    #+#             */
/*   Updated: 2025/04/30 14:11:49 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	lputchar(char c, int *r)
{
	write(1, &c, 1);
	(*r)++;
}

void	lputstr(char *s, int *r)
{
	int	i;

	i = -1;
	if (!s)
	{
		write(1, "(null)", 6);
		*r += 6;
		return ;
	}
	while (s[++i])
		lputchar(s[i], r);
}

void	lputnbr(int n, int *p_b)
{
	long int	nb;

	nb = n;
	if (nb == INT_MIN)
	{
		lputchar('-', p_b);
		nb *= -1;
	}
	if (nb < 0)
	{
		lputchar('-', p_b);
		nb = -nb;
	}
	if (nb > 9)
	{
		lputnbr(nb / 10, p_b);
		nb = nb % 10;
	}
	if (nb < 10)
		lputchar(nb + 48, p_b);
}

int	ft_skip_num(const char *s, int i)
{
	while (s[i] >= '0' && s[i] <= '9')
		i++;
	return (i);
}

void	init_info(t_info *info, const char *str, va_list *args)
{
	info->s = str;
	info->p_b = 0;
	info->i = 0;
	info->p_tmp = 0;
	info->u_tmp = 0;
	info->args = args;
}
