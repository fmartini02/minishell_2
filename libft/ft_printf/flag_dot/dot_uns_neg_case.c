/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot_uns_neg_case.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 17:06:49 by francema          #+#    #+#             */
/*   Updated: 2025/05/06 16:42:28 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static void	neg_width_greatest(t_flags *flags, t_info *info, unsigned int arg)
{
	int	width;
	int	n_len;

	width = flags->num;
	n_len = ft_num_len(arg, 10);
	if (arg == 0 && flags->dot == 0)
		return ;
	lputunsigned(arg, &(info->p_b));
	while (width > n_len++)
		lputchar(' ', &(info->p_b));
}

static void	neg_prec_greatest(t_info *info, t_flags *flags, unsigned int arg)
{
	int	prec;
	int	n_len;

	prec = flags->dot;
	if (arg < 0)
	{
		lputchar('-', &(info->p_b));
		arg *= -1;
	}
	n_len = ft_num_len(arg, 10);
	while (prec > n_len++)
		lputchar('0', &(info->p_b));
	lputunsigned(arg, &(info->p_b));
}

static void	neg_width_putin(t_flags *flags, t_info *info, unsigned int arg)
{
	int	d_len;
	int	n_len;
	int	flag;

	d_len = flags->dot;
	n_len = ft_num_len(arg, 10);
	flag = 0;
	if (arg < 0)
	{
		lputchar('-', &(info->p_b));
		arg *= -1;
		flag = 1;
		n_len = ft_num_len(arg, 10);
	}
	while (n_len++ < d_len)
		lputchar('0', &(info->p_b));
	lputunsigned(arg, &(info->p_b));
	if (flag)
		d_len++;
	if (d_len < flags->num)
	{
		while (d_len++ < flags->num)
			lputchar(' ', &(info->p_b));
	}
}

void	put_prec_uns_neg(t_flags *flags, t_info *info)
{
	int				n_len;
	unsigned int	arg;

	arg = va_arg(*(info->args), unsigned int);
	dot_edge_case(flags, info, arg, 'u');
	n_len = ft_num_len(arg, 10);
	if (arg < 0)
		n_len--;
	if (flags->num <= n_len && flags->dot <= n_len)
	{
		if (arg == 0 && flags->dot == 0)
			return ;
		lputunsigned(arg, &(info->p_b));
	}
	else if (flags->num > n_len && n_len > flags->dot)
		neg_width_greatest(flags, info, arg);
	else if (flags->num < n_len && n_len < flags->dot)
		neg_prec_greatest(info, flags, arg);
	else if (n_len < flags->num && n_len < flags->dot)
		neg_width_putin(flags, info, arg);
}
