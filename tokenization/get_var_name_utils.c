/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var_name_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalloli <mdalloli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:19:56 by mdalloli          #+#    #+#             */
/*   Updated: 2025/06/30 18:21:30 by mdalloli         ###   ########.fr       */
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
