/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   neg_zero_addr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:21:07 by francema          #+#    #+#             */
/*   Updated: 2025/04/30 14:13:01 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	neg_zero_char_case(t_flags *flags, t_info *info)
{
	int	n;
	int	i;

	n = va_arg(*(info->args), int);
	i = 0;
	lputchar(n, &(info->p_b));
	while (i++ < flags->num)
		lputchar(' ', &(info->p_b));
}

void	neg_zero_str_case(t_flags *flags, t_info *info)
{
	char	*arg;
	int		i;

	i = 0;
	arg = va_arg(*(info->args), char *);
	while (arg[i])
		lputchar(arg[i++], &(info->p_b));
	while (i++ < flags->num)
		lputchar(' ', &(info->p_b));
}

void	neg_zero_ptr_case(t_flags *flags, t_info *info)
{
	void	*ptr;
	int		nu_len;

	ptr = va_arg(*(info->args), void *);
	nu_len = ft_uns_len((unsigned long)ptr, 16, 1) + 2;
	if (!ptr)
		lputstr("(nil)", &(info->p_b));
	else
		ptr_case(ptr, info);
	while (nu_len++ < flags->num)
		lputchar(' ', &(info->p_b));
}
