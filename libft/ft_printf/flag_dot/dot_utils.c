/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:07:37 by francema          #+#    #+#             */
/*   Updated: 2025/04/30 14:14:21 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	dot_edge_case(t_flags *flags, t_info *info,
						unsigned long int arg, char c)
{
	int				n_prec;
	int				arg_int;
	unsigned int	arg_uns;

	n_prec = flags->dot;
	if (c == 'd' || c == 'i')
	{
		arg_int = (int)arg;
		if (n_prec == 0 && arg_int == 0)
			print_width(flags->num, 0, info, flags);
	}
	else if (c == 'u' || c == 'x' || c == 'X')
	{
		arg_uns = (unsigned int)arg;
		if (n_prec == 0 && arg_uns == 0)
			print_width(flags->num, 0, info, flags);
	}
	else if (c == 'p')
	{
		if (n_prec == 0 && arg == 0)
			print_width(flags->num, 0, info, flags);
	}
}

void	boh(char c, char *s, unsigned int arg)
{
	if (c == 'x')
		build_num(arg, "0123456789abcdef", s, 0);
	else
		build_num(arg, "0123456789ABCDEF", s, 0);
}

void	exa_dot_width_greatest(t_flags *flags, t_info *info, char *s)
{
	int	n_prec;

	n_prec = flags->dot;
	if (n_prec > (int)ft_strlen(s))
	{
		while (flags->num-- > n_prec)
			lputchar(' ', &(info->p_b));
	}
	else
	{
		while (flags->num-- > (int)ft_strlen(s))
			lputchar(' ', &(info->p_b));
	}
}
