/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_space.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 14:23:07 by francema          #+#    #+#             */
/*   Updated: 2025/04/30 14:13:38 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	handle_space(t_info *info, t_flags *flags, char c)
{
	if (c == 'c')
		space_char(va_arg(*(info->args), int), info, flags);
	else if (c == 's')
		space_str(va_arg(*(info->args), char *), info, flags);
	else if (c == 'x' || c == 'X')
		space_hexa(va_arg(*(info->args), int), info, flags, c);
	else if (c == 'p')
		space_adrr(va_arg(*(info->args), void *), info, flags);
	else if (c == 'u')
		space_uns(va_arg(*(info->args), unsigned int), info, flags);
	if (c == 'd' || c == 'i')
		space_int(va_arg(*(info->args), int), info, flags);
	flags->done = 1;
}
