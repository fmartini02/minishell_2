/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zero_num.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 16:57:10 by francema          #+#    #+#             */
/*   Updated: 2025/04/30 14:13:20 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	zero_int_case(t_flags *flags, t_info *info)
{
	long int	n;
	int			i;
	char		*arg;

	n = va_arg(*(info->args), int);
	i = 0;
	if (n < 0)
		lputchar('-', &(info->p_b));
	if (flags->pos)
		lputchar('+', &(info->p_b));
	while (i++ < (flags->num - ft_num_len(n, 10)))
		lputchar('0', &(info->p_b));
	if (n < 0)
		n *= -1;
	arg = ft_itoa(n);
	lputstr(arg, &(info->p_b));
	free(arg);
}

void	zero_uns_case(t_flags *flags, t_info *info)
{
	unsigned int	u;
	char			*arg;
	int				i;

	u = va_arg(*(info->args), unsigned int);
	arg = ft_utoa(u, 0);
	i = 0;
	while (i++ < (flags->num - ft_uns_len(u, 10, 0)))
		lputchar('0', &(info->p_b));
	i = 0;
	lputstr(arg, &(info->p_b));
	free(arg);
}

void	zero_exa_case(t_flags *flags, t_info *info, char c)
{
	char			*base;
	unsigned int	n;
	int				len;
	char			*tmp;

	base = "0123456789abcdef";
	if (c == 'X')
		base = "0123456789ABCDEF";
	n = va_arg(*(info->args), int);
	len = ft_uns_len(n, 16, 0);
	tmp = malloc(sizeof(char) * (len + 1));
	if (!tmp)
		return ;
	build_num(n, base, tmp, 0);
	while (len++ < flags->num)
		lputchar('0', &(info->p_b));
	lputstr(tmp, &(info->p_b));
	free(tmp);
}
