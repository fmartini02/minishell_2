/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandatory_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 12:00:14 by francema          #+#    #+#             */
/*   Updated: 2025/04/30 14:11:35 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	build_num(unsigned long int n, char *base, char *buf, int cast_type)
{
	int	len;
	int	l_base;

	l_base = ft_strlen(base);
	if (cast_type == 0)
		n = (unsigned int)n;
	else if (cast_type == 1)
		n = (unsigned long)n;
	else if (cast_type == 2)
		n = (unsigned long long)n;
	else if (cast_type == 3)
		n = (unsigned short)n;
	else if (cast_type == 4)
		n = (unsigned char)n;
	else if (cast_type == 5)
		n = (size_t)n;
	len = ft_uns_len(n, l_base, cast_type);
	buf[len--] = '\0';
	if (n == 0)
		buf[len--] = base[0];
	while (n > 0)
	{
		buf[len--] = base[n % l_base];
		n /= ft_strlen(base);
	}
}

void	lputunsigned(unsigned int n, int *p_b)
{
	char	*s;

	s = malloc(sizeof(char) * (ft_uns_len(n, 10, 0) + 1));
	if (!s)
		return ;
	build_num(n, "0123456789", s, 0);
	lputstr(s, p_b);
	free(s);
}

void	lputexa(unsigned int u, t_info *info, char c)
{
	char			*base;
	char			*buf;

	base = "0123456789abcdef";
	if (c == 'X')
		base = "0123456789ABCDEF";
	else if (c == '\0')
		lputstr("0x", &(info->p_b));
	buf = malloc(sizeof(char) * (ft_uns_len(u, 16, 0) + 1));
	if (!buf)
		return ;
	build_num(u, base, buf, 0);
	lputstr(buf, &(info->p_b));
	free(buf);
}

void	lputadrr(t_info *info)
{
	void	*p;
	char	*base;
	char	*buf;

	p = va_arg(*(info->args), void *);
	if (!p)
	{
		lputstr("(nil)", &(info->p_b));
		return ;
	}
	base = "0123456789abcdef";
	info->p_tmp = (unsigned long int) p;
	info->u_tmp = 0;
	buf = malloc(sizeof(char) * (ft_uns_len(info->p_tmp, 16, 1) + 1));
	if (!buf)
		return ;
	lputstr("0x", &(info->p_b));
	build_num(info->p_tmp, base, buf, 1);
	lputstr(buf, &(info->p_b));
	free(buf);
}

/*
if (n >= 0)
	nbr = n;
else
	nbr = UINT_MAX + n + 1;

COMPLEMENTO A DUE
*/
