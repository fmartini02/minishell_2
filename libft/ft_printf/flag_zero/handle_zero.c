/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_zero.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 12:41:10 by francema          #+#    #+#             */
/*   Updated: 2025/04/30 14:12:58 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	neg_zero_case(t_flags *flags, t_info *info, char c)
{
	if (c == 'c')
		neg_zero_char_case(flags, info);
	else if (c == 's')
		neg_zero_str_case(flags, info);
	else if (c == 'd' || c == 'i')
		neg_zero_int_case(flags, info);
	else if (c == 'u')
		neg_zero_uns_case(flags, info);
	else if (c == 'x' || c == 'X')
		neg_zero_exa_case(flags, info, c);
	else if (c == 'p')
		neg_zero_ptr_case(flags, info);
	else if (c == '%')
		lputchar('%', &info->p_b);
}

void	zero_case(t_flags *flags, t_info *info, char c)
{
	if (c == 'c')
		zero_char_case(flags, info);
	else if (c == 's')
		zero_str_case(flags, info);
	else if (c == 'd' || c == 'i')
		zero_int_case(flags, info);
	else if (c == 'u')
		zero_uns_case(flags, info);
	else if (c == 'x' || c == 'X')
		zero_exa_case(flags, info, c);
	else if (c == 'p')
		zero_ptr_case(flags, info);
	else if (c == '%')
		lputchar('%', &info->p_b);
}

void	handle_zero(t_flags *flags, t_info *info, char c)
{
	if (flags->neg)
		neg_zero_case(flags, info, c);
	else
		zero_case(flags, info, c);
	flags->done = 1;
}
