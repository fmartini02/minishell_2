/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   neg_width_num_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:08:01 by francema          #+#    #+#             */
/*   Updated: 2025/04/30 14:12:48 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	num_neg_int_case(t_info *info, t_flags *flags)
{
	int		arg_len;
	int		n;
	char	*arg;

	n = va_arg(*(info->args), int);
	arg_len = ft_num_len(n, 10);
	arg = ft_itoa(n);
	lputstr(arg, &(info->p_b));
	print_width(flags->num, arg_len, info, flags);
	free(arg);
}

void	num_neg_uns_case(t_info *info, t_flags *flags)
{
	int		nu_len;
	int		n;
	char	*tmp;

	nu_len = 0;
	n = va_arg(*(info->args), unsigned int);
	nu_len = ft_uns_len(n, 10, 0);
	tmp = malloc(sizeof(char) * (nu_len + 1));
	if (!tmp)
		return ;
	build_num(n, "0123456789", tmp, 0);
	lputstr(tmp, &(info->p_b));
	print_width(flags->num, nu_len, info, flags);
	free(tmp);
}

void	num_neg_exa_case(t_info *info, t_flags *flags, char c)
{
	int				nu_len;
	int				n;
	char			*tmp;

	n = va_arg(*(info->args), int);
	nu_len = ft_uns_len(n, 16, 0);
	tmp = malloc(sizeof(char) * (nu_len + 1));
	if (!tmp)
		return ;
	if (c == 'x')
		build_num(n, "0123456789abcdef", tmp, 0);
	else
		build_num(n, "0123456789ABCDEF", tmp, 0);
	lputstr(tmp, &(info->p_b));
	print_width(flags->num, nu_len, info, flags);
	free(tmp);
}
