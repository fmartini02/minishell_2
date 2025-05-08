/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot_uns_case.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 18:16:45 by francema          #+#    #+#             */
/*   Updated: 2025/05/06 16:42:07 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static void	width_greatest(t_flags *flags, t_info *info, unsigned int arg)
{
	int		width;
	int		n_len;

	width = flags->num;
	n_len = ft_uns_len(arg, 10, 0);
	if (arg == 0 && flags->dot == 0)
		return ;
	while (width > n_len++)
		lputchar(' ', &(info->p_b));
	lputunsigned(arg, &(info->p_b));
}

static void	prec_greatest(t_info *info, t_flags *flags, unsigned int arg)
{
	int	prec;
	int	n_len;

	prec = flags->dot;
	if (arg < 0)
	{
		lputchar('-', &(info->p_b));
		arg *= -1;
	}
	n_len = ft_uns_len(arg, 10, 0);
	while (prec > n_len++)
		lputchar('0', &(info->p_b));
	lputunsigned(arg, &(info->p_b));
}

static void	width_putin(t_flags *flags, t_info *info, unsigned int arg)
{
	int	d_len;
	int	n_len;

	d_len = flags->dot;
	n_len = ft_uns_len(arg, 10, 0);
	if (arg < 0)
		d_len++;
	if (d_len < flags->num)
	{
		while (d_len++ < flags->num)
			lputchar(' ', &(info->p_b));
	}
	if (arg < 0)
	{
		lputchar('-', &(info->p_b));
		arg *= -1;
		n_len = ft_uns_len(arg, 10, 0);
	}
	while (n_len++ < flags->dot)
		lputchar('0', &(info->p_b));
	lputunsigned(arg, &(info->p_b));
}

void	put_prec_uns(t_flags *flags, t_info *info)
{
	unsigned int	arg;
	int				n_len;

	arg = va_arg(*(info->args), unsigned int);
	dot_edge_case(flags, info, arg, 'u');
	n_len = ft_uns_len(arg, 10, 1);
	if (flags->num <= n_len && flags->dot <= n_len)
	{
		if (arg == 0 && flags->dot == 0)
			return ;
		lputunsigned(arg, &(info->p_b));
	}
	else if (flags->num > n_len && n_len > flags->dot)
		width_greatest(flags, info, arg);
	else if (flags->num < n_len && n_len < flags->dot)
		prec_greatest(info, flags, arg);
	else if (flags->num > n_len && n_len < flags->dot)
		width_putin(flags, info, arg);
}
