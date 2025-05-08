/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 14:15:14 by francema          #+#    #+#             */
/*   Updated: 2025/04/30 14:13:54 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	neg_pos_case(t_flags *flag, t_info *info, char c)
{
	if (c == 'c')
		neg_pos_char_case(flag, info);
	else if (c == 's')
		neg_pos_str_case(flag, info);
	else if (c == 'p')
		neg_pos_ptr_case(flag, info);
	else if (c == 'd' || c == 'i')
		neg_pos_int_case(flag, info);
	else if (c == 'u')
		neg_pos_uns_case(flag, info);
	else if (c == 'x' || c == 'X')
		neg_pos_hexa_case(flag, info, c);
}

void	pos_case(t_flags *flag, t_info *info, char c)
{
	if (c == 'c')
		pos_char_case(flag, info);
	else if (c == 's')
		pos_str_case(flag, info);
	else if (c == 'p')
		pos_ptr_case(flag, info);
	else if (c == 'd' || c == 'i')
		pos_int_case(flag, info);
	else if (c == 'u')
		pos_uns_case(flag, info);
	else if (c == 'x' || c == 'X')
		pos_hexa_case(flag, info, c);
}

void	handle_pos(t_flags *flags, t_info *info, char c)
{
	if (flags->neg)
		neg_pos_case(flags, info, c);
	else
		pos_case(flags, info, c);
	flags->done = 1;
}
