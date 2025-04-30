/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   neg_width_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:08:55 by francema          #+#    #+#             */
/*   Updated: 2025/04/30 14:12:44 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	num_neg_char_case(t_info *info, t_flags *flags)
{
	unsigned int	uns;

	uns = va_arg(*(info->args), int);
	lputchar(uns, &(info->p_b));
	print_width(flags->num, 1, info, flags);
}

void	num_neg_str_case(t_info *info, t_flags *flags)
{
	char	*str;
	int		str_len;

	str = va_arg(*(info->args), char *);
	if (!str)
		str = "(null)";
	str_len = ft_strlen(str);
	lputstr(str, &(info->p_b));
	print_width(flags->num, str_len, info, flags);
}

void	num_neg_ptr_case(t_info *info, t_flags *flags)
{
	unsigned long	nu;
	int				nu_len;
	void			*ptr;

	ptr = va_arg(*(info->args), void *);
	nu = (unsigned long)ptr;
	nu_len = ft_uns_len(nu, 16, 1) + 2;
	if (!ptr)
		nu_len = 5;
	if (!ptr)
		lputstr("(nil)", &(info->p_b));
	else
		ptr_case(ptr, info);
	print_width(flags->num, nu_len, info, flags);
}
