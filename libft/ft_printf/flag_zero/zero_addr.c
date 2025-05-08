/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zero_addr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 16:39:24 by francema          #+#    #+#             */
/*   Updated: 2025/04/30 14:13:10 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	zero_char_case(t_flags *flags, t_info *info)
{
	int	n;
	int	i;

	n = va_arg(*(info->args), int);
	i = 0;
	while (i++ < flags->num)
		lputchar(' ', &(info->p_b));
	lputchar(n, &(info->p_b));
}

void	zero_str_case(t_flags *flags, t_info *info)
{
	char	*arg;
	int		i;

	i = 0;
	arg = va_arg(*(info->args), char *);
	while (i++ < flags->num)
		lputchar(' ', &(info->p_b));
	lputstr(arg, &(info->p_b));
}

void	zero_ptr_case(t_flags *flags, t_info *info)
{
	void	*ptr;
	int		nu_len;

	ptr = va_arg(*(info->args), void *);
	nu_len = ft_uns_len((unsigned long)ptr, 16, 1) + 2;
	if (!ptr)
		lputstr("(nil)", &(info->p_b));
	while (nu_len++ < flags->num)
		lputchar(' ', &(info->p_b));
	if (ptr)
		ptr_case(ptr, info);
}
