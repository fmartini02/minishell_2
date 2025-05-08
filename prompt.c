#include "minishell.h"

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

char	*get_prompt(void)
{
	char 	*cwd;
	char 	*home;
	char	*prompt;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (NULL);
	home = getenv("HOME");
	if (home && ft_strncmp(cwd, home, ft_strlen(home)) == 0)
		prompt = home_prompt(cwd, home);
	else
		prompt = full_prompt(cwd);
	free(cwd);
	return (prompt);
}
