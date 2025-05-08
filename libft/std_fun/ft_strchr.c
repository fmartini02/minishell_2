/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <fmartini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 22:42:24 by fmartini          #+#    #+#             */
/*   Updated: 2024/01/27 22:42:24 by fmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*res;

	i = 0;
	while (s[i] != (unsigned char)c && s[i] != '\0')
		i++;
	if (s[i] == (unsigned char)c)
		res = (char *)s + i;
	else
		res = 0;
	return (res);
}
/*int main()
{
	char *s = "Hello World!";
	char c = 'W';
	printf("%s\n", ft_strchr(s, c + 256));
	printf("%s\n", strchr(s, c + 256));
	return (0);
}*/
