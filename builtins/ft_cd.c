/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 13:41:27 by mdalloli          #+#    #+#             */
/*   Updated: 2025/07/09 18:55:58 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Funzione helper: concatena "key=value"
static char	*str_key_value(const char *key, const char *value)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return (NULL);
	result = ft_strjoin(tmp, value);
	free(tmp);
	return (result);
}

void	ft_setenv(t_list **env, const char *key, const char *value)
{
	t_list	*node;
	size_t	key_len;
	char	*new_entry;

	node = *env;
	if (!key || !value)
		return ;
	key_len = ft_strlen(key);
	new_entry = str_key_value(key, value);
	if (!new_entry)
		return ;
	while (node)
	{
		if (!ft_strncmp((char *)node->content, key, key_len)
			&& ((char *)node->content)[key_len] == '=')
		{
			free(node->content);
			node->content = new_entry;
			return ;
		}
		node = node->next;
	}
	ft_lstadd_back(env, ft_lstnew(new_entry));
}

// static char	*get_oldpwd(void)
// {
// 	char	*oldpwd;
// 	size_t	i;

// 	oldpwd = getcwd(NULL, 0);
// 	i = 0;
// 	if (!oldpwd)
// 		return(NULL);
// 	return (oldpwd);
// }

static void	change_dir_and_update(t_mini *shell, char *oldpwd, char *path)
{
	char	cwd[PATH_MAX];

	if (chdir(path) != 0)
	{
		perror("cd");
		free(oldpwd);
		shell->last_exit_code = 1;
		return ;
	}
	if (!getcwd(cwd, sizeof(cwd)))
	{
		perror("cd");
		free(oldpwd);
		shell->last_exit_code = 1;
		return ;
	}
	ft_setenv(&shell->env, "OLDPWD", oldpwd);
	ft_setenv(&shell->env, "PWD", cwd);
	free(oldpwd);
	shell->last_exit_code = 0;
}

void	ft_cd(char **args, t_mini *shell)
{
	char	*oldpwd;
	char	*home;
	size_t	i;

	i = 0;
	oldpwd = getcwd(NULL, 0);
	if (!args[1]) // Caso: cd senza argomenti
	{
		home = ft_dollar_case(shell, "$HOME", &i); // oppure ft_getenv(shell->env, "HOME")
		if (home[0] == '\0')
		{
			ft_putendl_fd("cd: HOME not set", 2);
			shell->last_exit_code = 1;
			free(home);
			if (oldpwd)
				free(oldpwd);
			return ;
		}
		if (!oldpwd)
			oldpwd = ft_strdup(""); // o "UNKNOWN", o NULL se preferisci
		change_dir_and_update(shell, oldpwd, home);
		free(home);
	}
	else
	{
		if (!oldpwd)
			oldpwd = ft_strdup("");
		change_dir_and_update(shell, oldpwd, args[1]);
	}
}

