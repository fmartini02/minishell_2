/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <fmartini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 22:42:16 by fmartini          #+#    #+#             */
/*   Updated: 2024/01/27 22:42:16 by fmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "std_fun.h"
#include <stdio.h>

int	ft_skip_char(const char *s, int i, char c)
{
	while (s[i] && s[i] == c)
		i++;
	return (i);
}

int	ft_count_words(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] && s[i] == c)
			i = ft_skip_char(s, i, c);
		if (s[i] && s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

char	*get_word(const char *s, int i, char c)
{
	int		j;
	char	*str;

	j = 0;
	while (s[i + j] && s[i + j] != c)
		j++;
	str = malloc(sizeof(char) * (j + 1));
	if (!str)
		return (NULL);
	j = 0;
	while (s[i] && s[i] != c)
		str[j++] = s[i++];
	str[j] = '\0';
	return (str);
}

void	ft_split_utils(char **ret, const char *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == c)
			i = ft_skip_char(s, i, c);
		if (s[i] && s[i] != c)
		{
			ret[j++] = get_word(s, i, c);
			if (!ret[j - 1])
			{
				while (j >= 0)
					free(ret[j--]);
				free(ret);
				ret = NULL;
				return ;
			}
			while (s[i] && s[i] != c)
				i++;
		}
	}
	ret[j] = NULL;
}

char	**ft_split(char const *s, char c)
{
	char	**ret;

	if (!s)
		return (NULL);
	ret = malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
	if (!ret)
		return (NULL);
	ft_split_utils(ret, s, c);
	return (ret);
}
/*
int main()
{
	char *s = "isse";
	char **ret = ft_split(s, ' ');
	int i = 0;
	while (ret[i])
	{
		printf("%s\n", ret[i]);
		i++;
	}
	return (0);
}
*/
