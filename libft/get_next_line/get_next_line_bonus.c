/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:39:28 by francema          #+#    #+#             */
/*   Updated: 2025/04/29 18:27:14 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*extract_line(char **buffer)
{
	char	*line;
	char	*new_buf;
	int		i;

	if (!*buffer)
		return (NULL);
	i = 0;
	while ((*buffer)[i] && (*buffer)[i] != '\n')
		i++;
	if (!(*buffer)[i])
	{
		line = ft_strdup(*buffer);
		free(*buffer);
		*buffer = NULL;
		return (line);
	}
	line = ft_substr(*buffer, 0, i + 1);
	new_buf = ft_strdup(*buffer + i + 1);
	free(*buffer);
	*buffer = new_buf;
	if (!(*buffer))
		return (free(line), NULL);
	return (line);
}

char	*get_lines(int fd, char *buffer)
{
	char	tmp_buf[BUFFER_SIZE + 1];
	char	*tmp;
	int		b_read;

	b_read = 1;
	while (!ft_strchr(buffer, '\n') && b_read > 0)
	{
		b_read = read(fd, tmp_buf, BUFFER_SIZE);
		if (b_read < 0)
			return (free(buffer), NULL);
		tmp_buf[b_read] = '\0';
		tmp = ft_strjoin_gnl(buffer, tmp_buf);
		if (!tmp)
			return (free(buffer), NULL);
		free(buffer);
		buffer = tmp;
	}
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer[fd] = get_lines(fd, buffer[fd]);
	if (!buffer[fd] || !*buffer[fd])
		return (free(buffer[fd]), NULL);
	line = extract_line(&buffer[fd]);
	return (line);
}
