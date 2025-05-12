/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_till_char.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:07:31 by francema          #+#    #+#             */
/*   Updated: 2025/05/12 17:09:29 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlen_till_space(char *s, int i)
{
	size_t	len;

	len = 0;
	while (s[i] && !ft_ispace(s[i]))
	{
		len++;
		i++;
	}
	return (len);
}
