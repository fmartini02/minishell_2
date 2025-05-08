/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_mat_str.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:48:45 by francema          #+#    #+#             */
/*   Updated: 2025/04/30 17:34:35 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf/ft_printf.h"

void	ft_print_mat_str(void *mat, int depth)
{
	void	**ptrs;
	char	**strs;
	int		i;

	if (!mat)
		return;
	i = 0;
	if (depth == 1)
	{
		strs = (char **)mat;
		while (strs[i])
		{
			ft_putstr(strs[i++]);
			ft_putchar('\n');
		}
	}
	else
	{
		ptrs = (void **)mat;
		while (ptrs[i])
			ft_print_mat_str(ptrs[i++], depth - 1);
	}
}
