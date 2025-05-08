/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pos_case.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:13:32 by francema          #+#    #+#             */
/*   Updated: 2025/04/30 14:14:03 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	pos_char_case(t_flags *flag, t_info *info)
{
	char	c;

	c = va_arg(*(info->args), int);
	print_width(flag->num - 1, 1, info, flag);
	lputchar(c, &(info->p_b));
}

void	pos_str_case(t_flags *flag, t_info *info)
{
	char	*s;

	s = va_arg(*(info->args), char *);
	if (!s)
		s = "(null)";
	print_width(flag->num - ft_strlen(s), ft_strlen(s), info, flag);
	lputstr(s, &(info->p_b));
}

void	pos_ptr_case(t_flags *flags, t_info *info)
{
	void	*ptr;
	int		ptr_len;
	char	*s;

	ptr = va_arg(*(info->args), void *);
	if (!ptr)
	{
		lputstr("(nil)", &(info->p_b));
		return ;
	}
	ptr_len = ft_uns_len((unsigned long)ptr, 16, 1) + 3;
	print_width(flags->num - ptr_len, ptr_len, info, flags);
	lputstr("+0x", &(info->p_b));
	s = malloc(ptr_len - 2);
	if (!s)
		return ;
	build_num((unsigned long)ptr, "0123456789abcdef", s, 1);
	ptr_len = ft_strlen(s);
	if (flags->dot)
	{
		while (flags->dot > ptr_len++)
			lputchar('0', &(info->p_b));
	}
	lputstr(s, &(info->p_b));
	free(s);
}
