/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 09:47:53 by francema          #+#    #+#             */
/*   Updated: 2025/04/30 14:11:31 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	handle_specflag(t_flags *flags, t_info *info)
{
	const char	*s;
	char		c;

	s = info->s;
	c = s[info->i];
	if (flags->zero && !flags->sharp && flags->num && flags->dot == -1)
		handle_zero(flags, info, c);
	else if (flags->space && !flags->pos && !flags->neg)
		handle_space(info, flags, c);
	else if (flags->sharp && (c == 'x' || c == 'X'))
		handle_sharp(info, c, flags);
	else if (flags->dot != -1)
		handle_dot(flags, info, c);
	else if (flags->num && !flags->done)
	{
		if (flags->neg)
			neg_case(info, c, flags);
		else
			handle_num(info, c, flags);
	}
	else if (flags->pos)
		handle_pos(flags, info, c);
	if (!flags->done)
		expand_flags(info);
}

void	spec_flag(t_info *info)
{
	int			i;
	t_flags		*flags;
	const char	*s;

	flags = malloc(sizeof(t_flags) * 1);
	if (!flags)
		return ;
	flags->num = 0;
	flags->done = 0;
	flags->zero = 0;
	flags->space = 0;
	flags->dot = -1;
	flags->neg = 0;
	flags->pos = 0;
	flags->sharp = 0;
	flags->dub = 0;
	s = info->s;
	i = info->i;
	while (check_stdflags(s[i]))
		i = init_flags(s[i], flags, info, &i);
	info->i = i;
	handle_specflag(flags, info);
	free(flags);
}

void	expand_flags(t_info *info)
{
	const char	*str;
	int			j;

	str = info->s;
	j = info->i;
	if (check_stdflags(str[j]))
		spec_flag(info);
	else if (str[j] == 's')
		lputstr(va_arg(*(info->args), char *), &(info->p_b));
	else if (str[j] == 'c')
		lputchar(va_arg(*(info->args), int), &(info->p_b));
	else if (str[j] == 'd' || str[j] == 'i')
		lputnbr(va_arg(*(info->args), int), &(info->p_b));
	else if (str[j] == 'u')
		lputunsigned(va_arg(*(info->args), unsigned), &(info->p_b));
	else if (str[j] == 'x' || str[j] == 'X')
		lputexa(va_arg(*(info->args), int), info, str[j]);
	else if (str[j] == 'p')
		lputadrr(info);
	else if (str[j] == '%')
		lputchar('%', &(info->p_b));
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	t_info	*info;
	int		p_b;

	va_start(args, str);
	info = malloc(sizeof(t_info));
	if (!info || !str)
		return (-1);
	init_info(info, str, &args);
	while (info->s[info->i])
	{
		if (info->s[info->i] == '%')
		{
			(info->i)++;
			expand_flags(info);
		}
		else
			lputchar(info->s[info->i], &(info->p_b));
		(info->i)++;
	}
	p_b = info->p_b;
	free(info);
	va_end(args);
	return (p_b);
}
