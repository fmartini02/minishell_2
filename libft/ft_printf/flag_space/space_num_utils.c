/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_num_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:49:56 by francema          #+#    #+#             */
/*   Updated: 2025/04/30 14:13:45 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	space_uns(unsigned int n, t_info *info, t_flags *flags)
{
	char	*tmp;
	int		len;

	tmp = malloc(sizeof(char) * ft_uns_len(n, 10, 1) + 1);
	if (!tmp)
		return ;
	build_num(n, "0123456789", tmp, 1);
	len = ft_strlen(tmp);
	print_width(len, len, info, flags);
	lputstr(tmp, &(info->p_b));
	free(tmp);
}

void	space_hexa(unsigned int n, t_info *info, t_flags *flags, char c)
{
	char	*tmp;
	int		len;

	tmp = malloc(sizeof(char) * ft_uns_len(n, 16, 1) + 1);
	if (!tmp)
		return ;
	if (c == 'x')
		build_num(n, "0123456789abcdef", tmp, 1);
	else
		build_num(n, "0123456789ABCDEF", tmp, 1);
	len = ft_strlen(tmp);
	print_width(len, len, info, flags);
	lputstr(tmp, &(info->p_b));
	free(tmp);
}

void	space_int(int n, t_info *info, t_flags *flags)
{
	if (n >= 0)
		lputchar(' ', &(info->p_b));
	print_width(flags->num, ft_num_len(n, 10), info, flags);
	lputnbr(n, &(info->p_b));
}
