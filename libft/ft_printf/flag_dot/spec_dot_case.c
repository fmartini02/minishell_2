/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spec_dot_case.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:27:51 by francema          #+#    #+#             */
/*   Updated: 2025/05/06 16:44:01 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	dot_char_case(t_flags *flags, t_info *info)
{
	char	c;
	int		n_width;

	c = va_arg(*(info->args), int);
	n_width = flags->num;
	while (n_width-- > 1)
		lputchar(' ', &(info->p_b));
	lputchar(c, &(info->p_b));
}

void	dot_str_case(t_flags *flags, t_info *info)
{
	char	*s;
	int		n_width;
	int		i;
	int		s_len;

	s = va_arg(*(info->args), char *);
	n_width = flags->num;
	i = 0;
	if (!s)
	{
		if (flags->dot >= 6)
			s = "(null)";
		else
			s = "";
	}
	s_len = ft_strlen(s);
	if (flags->dot < s_len && flags->dot != -1)
		s_len = flags->dot;
	while (n_width-- > s_len)
		lputchar(' ', &(info->p_b));
	while (s[i] && i < flags->dot)
		lputchar(s[i++], &(info->p_b));
}

void	dot_exa_case(t_flags *flags, t_info *info, char c)
{
	unsigned int	arg;
	char			*s;

	arg = va_arg(*(info->args), int);
	dot_edge_case(flags, info, arg, c);
	if (flags->dot == 0 && arg == 0)
		return ;
	s = malloc(sizeof(char) * (ft_uns_len(arg, 16, 0) + 1));
	if (!s)
		return ;
	boh(c, s, arg);
	if (flags->num > flags->dot && flags->num > (int)ft_strlen(s))
		exa_dot_width_greatest(flags, info, s);
	if (flags->dot > (int)ft_strlen(s))
	{
		while (flags->dot-- > (int)ft_strlen(s))
			lputchar('0', &(info->p_b));
	}
	lputstr(s, &(info->p_b));
	free(s);
}

void	dot_ptr_case(t_flags *flags, t_info *info)
{
	void	*ptr;
	char	*s;

	ptr = va_arg(*(info->args), void *);
	s = malloc(sizeof(char) * (ft_uns_len((unsigned long)ptr, 16, 1) + 1));
	if (!s)
		return ;
	build_num((unsigned long)ptr, "0123456789abcdef", s, 1);
	if (flags->num > flags->dot && flags->num > ((int)ft_strlen(s) + 2))
	{
		while (flags->num-- > ((int)ft_strlen(s) + 2))
			lputchar(' ', &(info->p_b));
	}
	lputstr("0x", &(info->p_b));
	if (flags->dot > ((int)ft_strlen(s) + 2))
	{
		while (flags->dot-- > ((int)ft_strlen(s) + 2))
			lputchar('0', &(info->p_b));
		lputstr(s, &(info->p_b));
	}
	lputstr(s, &(info->p_b));
	free (s);
}

void	spec_dot_cases(t_flags *flags, t_info *info, char c)
{
	if (c == 'c')
		dot_char_case(flags, info);
	else if (c == 's')
		dot_str_case(flags, info);
	else if (c == 'x' || c == 'X')
		dot_exa_case(flags, info, c);
	else if (c == 'p')
		dot_ptr_case(flags, info);
}
