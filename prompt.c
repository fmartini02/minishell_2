/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:23:02 by mdalloli          #+#    #+#             */
/*   Updated: 2025/07/09 19:15:48 by francema         ###   ########.fr       */
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
char	*get_prompt(t_mini *shell)
{
	char	*cwd;
	char	*home;
	char	*prompt;
	size_t	i;

	cwd = getcwd(NULL, 0);
	i = 0;
	if (!cwd)
	{
		prompt = ft_dollar_case(shell, "$PWD", &i);
		home = ft_dollar_case(shell, "$HOME", &i);
		if (home && ft_strncmp(prompt, home, ft_strlen(home)) == 0)
			prompt = home_prompt(prompt, home);
		free(home);
		return (prompt);
	}
	home = ft_dollar_case(shell, "$HOME", &i);
	if (home && ft_strncmp(cwd, home, ft_strlen(home)) == 0)
		prompt = home_prompt(cwd, home);
	else
		prompt = full_prompt(cwd);
	free(cwd);
	free(home);
	return (prompt);
}
