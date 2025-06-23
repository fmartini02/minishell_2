#include "minishell.h"

char	**env_list_to_array(t_list *env)
{
	char	**envp;
	t_list	*current;
	int		count;
	int		i;

	// 1. Conta gli elementi nella lista
	count = 0;
	current = env;
	while (current)
	{
		count++;
		current = current->next;
	}

	// 2. Alloca spazio per il char *array (+1 per NULL finale)
	envp = malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return (NULL);

	// 3. Copia i contenuti dalla lista all'array
	current = env;
	i = 0;
	while (current)
	{
		envp[i] = ft_strdup((char *)current->content);
		if (!envp[i])
		{
			free_split(envp);
			return (NULL);
		}
		i++;
		current = current->next;
	}
	envp[i] = NULL;

	return (envp);
}
