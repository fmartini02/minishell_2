/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dot_case.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 17:10:14 by francema          #+#    #+#             */
/*   Updated: 2025/04/30 14:14:17 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	put_dot_case(t_flags *flags, t_info *info, char c)
{
	if (flags->neg)
	{
		if (c == 'u')
			put_prec_uns_neg(flags, info);
		else
			put_prec_num_neg(flags, info);
	}
	else
	{
		if (c == 'u')
			put_prec_uns(flags, info);
		else
			put_prec_num(flags, info);
	}
}

void	handle_dot(t_flags *flags, t_info *info, char c)
{
	int		prec_len;
	int		i;

	prec_len = flags->dot;
	i = 0;
	if (c != 'i' && c != 'd' && c != 'u' )
	{
		if (flags->neg)
			spec_dot_neg_case(flags, info, c);
		else
			spec_dot_cases(flags, info, c);
	}
	else
		put_dot_case(flags, info, c);
	flags->done = 1;
}
