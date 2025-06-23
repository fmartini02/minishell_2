#include "../minishell.h"

static int	env_list_count(t_list *env)
{
	int	count = 0;

	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

static int	fill_env_array(char **envp, t_list *env)
{
	int	i = 0;

	while (env)
	{
		envp[i] = ft_strdup((char *)env->content);
		if (!envp[i])
			return (-1);
		env = env->next;
		i++;
	}
	envp[i] = NULL;
	return (0);
}

char	**env_list_to_array(t_list *env)
{
	char	**envp;
	int		count;

	count = env_list_count(env);
	envp = malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return (NULL);
	if (fill_env_array(envp, env) < 0)
	{
		free_split(envp);
		return (NULL);
	}
	return (envp);
}
