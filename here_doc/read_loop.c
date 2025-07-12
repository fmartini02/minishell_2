/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 21:55:41 by francema          #+#    #+#             */
/*   Updated: 2025/07/12 15:46:51 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*remove_quotes(const char *s)
{
	char	*new_s;
	int		i;
	int		j;
	size_t	len;

	j = 0;
	i = 0;
	if (!s)
		return (NULL);
	len = strlen(s);
	new_s = malloc(len + 1);
	if (!new_s)
		return (NULL);
	while (s[i])
	{
		if (s[i] != '\'' && s[i] != '"')
			new_s[j++] = s[i];
		i++;
	}
	new_s[j] = '\0';
	return (new_s);
}

bool	should_expand(char **eof)
{
	char	*tmp;

	if (ft_strchr(*eof, '\'') || ft_strchr(*eof, '"'))
	{
		tmp = remove_quotes(*eof);
		if (!tmp)
			return (false);
		*eof = tmp;
		return (false);
	}
	return (true);
}

int	write_in_pipe(char *line, char *eof,
	int pip_fd, t_mini *shell)
{
	bool	expand;

	expand = should_expand(&eof);
	if (ft_strcmp(line, eof) == 0)
	{
		free(line);
		return (0);
	}
	if (!expand)
	{
		write(pip_fd, line, ft_strlen(line));
		write(pip_fd, "\n", 1);
		free(line);
	}
	else
		apply_doll_exansion(pip_fd, line, shell);
	return (1);
}

int	heredoc_read_loop(
	int pip_fd, char *eof, struct sigaction *old_sa, t_mini *shell)
{
	char	*line;
	char	*original;

	original = eof;
	while (1)
	{
		line = readline("> ");
		if (g_sig_code == 130)
			return (free(line), sigaction_return(old_sa, -1));
		if (!line)
			return (write_ctrld(eof), sigaction_return(old_sa, -1));
		if (!write_in_pipe(line, eof, pip_fd, shell))
			break ;
	}
	if (original != eof)
		free(eof);
	return (sigaction_return(old_sa, 0));
}
