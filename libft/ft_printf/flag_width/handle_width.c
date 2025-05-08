/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_width.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 12:06:58 by francema          #+#    #+#             */
/*   Updated: 2025/05/06 16:46:21 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	print_width(int width, int len, t_info *info, t_flags *flags)
{
	while ((width - len) > 0)
	{
		if (flags->zero)
			lputchar('0', &(info->p_b));
		else
			lputchar(' ', &(info->p_b));
		len++;
	}
}

void	neg_case(t_info *info, char c, t_flags *flags)
{
	if (c == 'c')
		num_neg_char_case(info, flags);
	else if (c == 'd' || c == 'i')
		num_neg_int_case(info, flags);
	else if (c == 'x' || c == 'X')
		num_neg_exa_case(info, flags, c);
	else if (c == 'u')
		num_neg_uns_case(info, flags);
	else if (c == 'p')
		num_neg_ptr_case(info, flags);
	else if (c == 's')
		num_neg_str_case(info, flags);
	else
		return ;
	flags->done = 1;
}

void	handle_num(t_info *info, char c, t_flags *flags)
{
	if (c == 'c')
		num_char_case(info, flags);
	else if (c == 'd' || c == 'i')
		num_int_case(info, flags);
	else if (c == 'x' || c == 'X')
		num_exa_case(info, flags, c);
	else if (c == 'u')
		num_uns_case(info, flags);
	else if (c == 'p')
		num_ptr_case(info, flags);
	else if (c == 's')
		num_str_case(info, flags);
	else
		return ;
	flags->done = 1;
}
