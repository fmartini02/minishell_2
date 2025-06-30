/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var_name.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalloli <mdalloli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:26:45 by francema          #+#    #+#             */
/*   Updated: 2025/06/30 11:01:25 by mdalloli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	get_doll_indx(char *s, size_t i)
{
	if (!s)
		return (-1);
	while (i > 0 && s[i] != '$')
		i--;
	return (i);
}

size_t	get_start_indx(char *s, size_t doll_indx)
{
	while (doll_indx > 0 && s[doll_indx])
	{
		doll_indx--;
		if (s[doll_indx] == '>' || s[doll_indx] == '<')
		{
			doll_indx++;
			break ;
		}
		if (doll_indx > 0 && s[doll_indx] == '\'')
		{
			doll_indx--;
			while (doll_indx > 0 && s[doll_indx] != '\'')
				doll_indx--;
		}
		else if (doll_indx > 0 && s[doll_indx] == '"')
		{
			doll_indx--;
			while (doll_indx > 0 && s[doll_indx] != '"')
				doll_indx--;
		}
	}
	return (doll_indx);
}

size_t	get_end_indx(char *s, size_t doll_indx)
{
	while (s[doll_indx] && s[doll_indx] != ' ')
	{
		doll_indx++;
		if (s[doll_indx] == '>' || s[doll_indx] == '<')
		{
			doll_indx--;
			break ;
		}
		if (s[doll_indx] == '\'')
		{
			doll_indx++;
			while (s[doll_indx] && s[doll_indx] != '\'')
				doll_indx++;
		}
		else if (s[doll_indx] == '"')
		{
			doll_indx++;
			while (s[doll_indx] && s[doll_indx] != '"')
				doll_indx++;
		}
	}
	return (doll_indx);
}

char	*space_notspace_case(char *s, t_mini *shell, size_t *i)
{
	size_t	end;
	size_t	start;
	size_t	doll_indx;
	char	*name;

	doll_indx = get_doll_indx(s, *i);
	start = doll_indx;
	end = get_end_indx(s, doll_indx);
	name = ft_substr(s, start, end - start);
	if (!name)
		ft_fatal_memerr(shell);
	return (name);
}

char	*notspace_notspace_case(char *s, t_mini *shell, size_t *i)
{
	int		start;
	int		end;
	char	*name;

	start = get_start_indx(s, get_doll_indx(s, *i));
	end = get_end_indx(s, get_doll_indx(s, *i));
	name = ft_substr(s, start, end - start);
	if (!name)
		ft_fatal_memerr(shell);
	return (name);
}

char	*notspace_space_case(char *s, t_mini *shell, size_t *i)
{
	size_t	start;
	size_t	end;
	size_t	doll_indx;
	char	*name;

	doll_indx = get_doll_indx(s, *i);
	start = get_start_indx(s, doll_indx);
	end = *i;
	name = ft_substr(s, start, end - start);
	if (!name)
		ft_fatal_memerr(shell);
	return (name);
}

char	*space_space_case(char *s, t_mini *shell, size_t *i)
{
	size_t	doll_indx;
	size_t	end;
	char	*name;

	doll_indx = get_doll_indx(s, *i);
	end = doll_indx;
	while (s[end] && !ft_ispecial_char(s[end]))
		end++;
	name = ft_substr(s, doll_indx, end - doll_indx);
	if (!name)
		ft_fatal_memerr(shell);
	return (name);
}

char	*get_var_name(char *s, char *content, size_t *i, t_mini *shell)
{
	if (content[0] == ' ' && content[ft_strlen(content) - 1] != ' ')
		return (space_notspace_case(s, shell, i));
	else if (content[0] != ' ' && content[ft_strlen(content) - 1] != ' ')
		return (notspace_notspace_case(s, shell, i));
	else if (content[0] != ' ' && content[ft_strlen(content) - 1] == ' ')
		return (notspace_space_case(s, shell, i));
	else if (content[0] == ' ' && content[ft_strlen(content) - 1] == ' ')
		return (space_space_case(s, shell, i));
	else
		return (NULL);
}
