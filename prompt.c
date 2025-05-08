#include "minishell.h"

char	*get_prompt(void)
{
	char 	*cwd;
	char 	*home;
	char	*path;
	char	*prompt;
	size_t	len;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (NULL);
	home = getenv("HOME");
	if (home && ft_strncmp(cwd, home, ft_strlen(home)) == 0)
	{
		path = cwd + ft_strlen(home);
		if (*path == '/')
			path++;
		len = ft_strlen("~") + ft_strlen(path) + ft_strlen("$ ") + 2;
		prompt = malloc(len);
		if (!prompt)
		{
			free(cwd);
			return (NULL);
		}
		prompt[0] = '\0';
		ft_strlcat(prompt, "~", len);
		if (*path)
		{
			ft_strlcat(prompt, "/", len);
			ft_strlcat(prompt, path, len);
		}
		ft_strlcat(prompt, "$ ", len);
	}
	else
	{
		len = ft_strlen(cwd) + ft_strlen("$ ") + 2;
		prompt = malloc(len);
		if (!prompt)
		{
			free(cwd);
			return (NULL);
		}
		prompt[0] = '\0';
		ft_strlcat(prompt, cwd, len);
		ft_strlcat(prompt, "$ ", len);
	}
	free(cwd);
	return (prompt);
}
