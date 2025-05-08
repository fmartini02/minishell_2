/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pos_num_case.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:27:52 by francema          #+#    #+#             */
/*   Updated: 2025/04/30 14:14:07 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	pos_int_case(t_flags *flags, t_info *info)
{
	int	n;
	int	n_len;

	n = va_arg(*(info->args), int);
	n_len = ft_num_len(n, 10) + flags->dot;
	print_width(flags->num - n_len, n_len, info, flags);
	n_len = ft_num_len(n, 10);
	if (n >= 0)
	{
		n_len++;
		lputchar('+', &(info->p_b));
	}
	if (flags->dot)
	{
		while (flags->dot > n_len++)
			lputchar('0', &(info->p_b));
	}
	lputnbr(n, &(info->p_b));
}

void	pos_uns_case(t_flags *flags, t_info *info)
{
	unsigned int	u;
	int				u_len;

	u = va_arg(*(info->args), unsigned int);
	u_len = ft_uns_len(u, 10, 0) + flags->dot;
	print_width(flags->num - u_len, u_len, info, flags);
	u_len = ft_uns_len(u, 10, 0);
	if (flags->dot)
	{
		while (flags->dot > u_len++)
			lputchar('0', &(info->p_b));
	}
	lputunsigned(u, &(info->p_b));
}

void	pos_hexa_case(t_flags *flags, t_info *info, char c)
{
	unsigned int	u;
	int				u_len;
	char			*s;

	u = va_arg(*(info->args), unsigned int);
	u_len = ft_uns_len(u, 16, 0) + flags->dot;
	print_width(flags->num - u_len, u_len, info, flags);
	u_len = ft_uns_len(u, 16, 0);
	s = malloc(u_len + 1);
	if (!s)
		return ;
	if (c == 'x')
		build_num(u, "0123456789abcdef", s, 0);
	else
		build_num(u, "0123456789ABCDEF", s, 0);
	if (flags->dot)
	{
		while (flags->dot > u_len++)
			lputchar('0', &(info->p_b));
	}
	lputstr(s, &(info->p_b));
	free(s);
}
