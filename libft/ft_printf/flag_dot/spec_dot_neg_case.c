/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spec_dot_neg_case.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:19:27 by francema          #+#    #+#             */
/*   Updated: 2025/04/30 14:14:12 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	dot_neg_char_case(t_flags *flags, t_info *info)
{
	char	c;
	int		n_width;

	c = va_arg(*(info->args), int);
	n_width = flags->num;
	lputchar(c, &(info->p_b));
	while (n_width-- > 1)
		lputchar(' ', &(info->p_b));
}

void	dot_neg_str_case(t_flags *flags, t_info *info)
{
	char	*s;
	int		n_width;
	int		s_len;
	int		i;

	s = va_arg(*(info->args), char *);
	n_width = flags->num;
	if (!s)
	{
		if (flags->dot >= 6)
			s = "(null)";
		else
			s = "";
	}
	s_len = ft_strlen(s);
	i = 0;
	if (flags->dot < s_len && flags->dot != -1)
		s_len = flags->dot;
	while (s[i] && i < flags->dot)
		lputchar(s[i++], &(info->p_b));
	while (n_width-- > s_len)
		lputchar(' ', &(info->p_b));
}

void	dot_neg_exa_case(t_flags *flags, t_info *info, char c)
{
	unsigned int	arg;
	char			*s;
	int				n_prec;

	arg = va_arg(*(info->args), int);
	n_prec = flags->dot;
	dot_edge_case(flags, info, arg, c);
	if (arg == 0 && n_prec == 0)
		return ;
	s = malloc(sizeof(char) * (ft_uns_len(arg, 16, 0) + 1));
	if (!s)
		return ;
	boh(c, s, arg);
	if (n_prec > (int)ft_strlen(s))
	{
		while (n_prec-- > (int)ft_strlen(s))
			lputchar('0', &(info->p_b));
	}
	if (flags->num > flags->dot && flags->num > (int)ft_strlen(s))
	{
		lputstr(s, &(info->p_b));
		exa_dot_width_greatest(flags, info, s);
	}
	else
		lputstr(s, &(info->p_b));
}

void	dot_neg_ptr_case(t_flags *flags, t_info *info)
{
	void	*ptr;
	char	*s;
	int		n_prec;

	ptr = va_arg(*(info->args), void *);
	n_prec = flags->dot;
	s = malloc(sizeof(char) * (ft_uns_len((unsigned long)ptr, 16, 1) + 1));
	if (!s)
		return ;
	build_num((unsigned long)ptr, "0123456789abcdef", s, 1);
	lputstr("0x", &(info->p_b));
	if (n_prec > ((int)ft_strlen(s) + 2))
	{
		while (n_prec-- > ((int)ft_strlen(s) + 2))
			lputchar('0', &(info->p_b));
		lputstr(s, &(info->p_b));
	}
	lputstr(s, &(info->p_b));
	if (flags->num > flags->dot && flags->num > ((int)ft_strlen(s) + 2))
	{
		while (flags->num-- > ((int)ft_strlen(s) + 2))
			lputchar(' ', &(info->p_b));
	}
	free(s);
}

void	spec_dot_neg_case(t_flags *flags, t_info *info, char c)
{
	if (c == 'c')
		dot_neg_char_case(flags, info);
	else if (c == 's')
		dot_neg_str_case(flags, info);
	else if (c == 'x' || c == 'X')
		dot_neg_exa_case(flags, info, c);
	else if (c == 'p')
		dot_neg_ptr_case(flags, info);
}
