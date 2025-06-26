/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalloli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:23:02 by mdalloli          #+#    #+#             */
/*   Updated: 2025/06/25 12:23:03 by mdalloli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Creates the prompt from the home directory
If cwd (current working directory) starts with $HOME, replaces it with '~'*/
static char	*home_prompt(char *cwd, char *home)
{
	char	*path;
	char	*prompt;
	size_t	len;

	path = cwd + ft_strlen(home);
	if (*path == '/')
		path++;
	len = ft_strlen("~") + ft_strlen(path) + ft_strlen("$ ") + 2;
	prompt = malloc(len);
	if (!prompt)
		return (NULL);
	prompt[0] = '\0';
	ft_strlcat(prompt, "~", len);
	if (*path)
	{
		ft_strlcat(prompt, "/", len);
		ft_strlcat(prompt, path, len);
	}
	ft_strlcat(prompt, "$ ", len);
	return (prompt);
}

/* Creates the full prompt with the absolute directory.
Used when the current working directory (cwd) is NOT under $HOME. */
static char	*full_prompt(char *cwd)
{
	char	*prompt;
	size_t	len;

	len = ft_strlen(cwd) + ft_strlen("$ ") + 2;
	prompt = malloc(len);
	if (!prompt)
		return (NULL);
	prompt[0] = '\0';
	ft_strlcat(prompt, cwd, len);
	ft_strlcat(prompt, "$ ", len);
	return (prompt);
}

/* Returns the prompt to display to the user.
If the current directory is under $HOME, use '~', 
otherwise use the full path. */
char	*get_prompt(void)
{
	char	*cwd;
	char	*home;
	char	*prompt;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("getcwd");
		return (ft_strdup("minishell$ "));
	}
	home = getenv("HOME");
	if (home && ft_strncmp(cwd, home, ft_strlen(home)) == 0)
		prompt = home_prompt(cwd, home);
	else
		prompt = full_prompt(cwd);
	free(cwd);
	return (prompt);
}
