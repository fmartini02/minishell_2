/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:28:33 by francema          #+#    #+#             */
/*   Updated: 2025/05/06 16:44:37 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	space_char(int c, t_info *info, t_flags *flags)
{
	print_width(1, 1, info, flags);
	lputchar(c, &(info->p_b));
}

void	space_str(char *s, t_info *info, t_flags *flags)
{
	print_width(flags->num, ft_strlen(s), info, flags);
	if (!s)
		s = "(null)";
	lputstr(s, &(info->p_b));
}

void	space_adrr(void *p, t_info *info, t_flags *flags)
{
	unsigned long int	n;
	char				*tmp;

	n = (unsigned long int)p;
	tmp = malloc(sizeof(char) * ft_uns_len(n, 16, 1) + 1);
	if (!tmp)
		return ;
	build_num(n, "0123456789abcdef", tmp, 1);
	lputstr("0x", &(info->p_b));
	print_width(0, 2, info, flags);
}
