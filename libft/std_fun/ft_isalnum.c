/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <fmartini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 22:37:19 by fmartini          #+#    #+#             */
/*   Updated: 2024/01/27 22:37:19 by fmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "std_fun.h"

int	ft_isalnum(int c)
{
	int	res;

	if (ft_isalpha(c) || ft_isdigit(c))
		res = 1;
	else
		res = 0;
	return (res);
}
