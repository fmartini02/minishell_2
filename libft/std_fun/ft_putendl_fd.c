/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <fmartini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 22:41:43 by fmartini          #+#    #+#             */
/*   Updated: 2024/01/27 22:41:43 by fmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "std_fun.h"

void	ft_putendl_fd(char *s, int fd)
{
	char	n;

	n = '\n';
	if (fd < 0)
		return ;
	write(fd, s, ft_strlen(s));
	write(fd, &n, 1);
}
