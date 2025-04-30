/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   width_num_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:11:26 by francema          #+#    #+#             */
/*   Updated: 2025/04/30 14:12:40 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	num_int_case(t_info *info, t_flags *flags)
{
	int		arg_len;
	int		n;
	char	*arg;

	n = va_arg(*(info->args), int);
	arg = ft_itoa(n);
	if (!arg)
		return ;
	arg_len = ft_strlen((const char *) arg);
	print_width(flags->num, arg_len, info, flags);
	lputstr(arg, &(info->p_b));
	free(arg);
}

void	num_uns_case(t_info *info, t_flags *flags)
{
	int		nu_len;
	int		n;
	char	*tmp;

	nu_len = 0;
	n = va_arg(*(info->args), unsigned int);
	nu_len = ft_uns_len(n, 10, 0);
	print_width(flags->num, nu_len, info, flags);
	tmp = malloc(sizeof(char) * (nu_len + 1));
	if (!tmp)
		return ;
	build_num(n, "0123456789", tmp, 0);
	lputstr(tmp, &(info->p_b));
	free(tmp);
}

void	num_exa_case(t_info *info, t_flags *flags, char c)
{
	int				nu_len;
	int				n;
	char			*tmp;

	n = va_arg(*(info->args), int);
	nu_len = ft_uns_len(n, 16, 0);
	print_width(flags->num, nu_len, info, flags);
	tmp = malloc(sizeof(char) * (nu_len + 1));
	if (!tmp)
		return ;
	if (c == 'x')
		build_num(n, "0123456789abcdef", tmp, 0);
	else
		build_num(n, "0123456789ABCDEF", tmp, 0);
	lputstr(tmp, &(info->p_b));
	free(tmp);
}
