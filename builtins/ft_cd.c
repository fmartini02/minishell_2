/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:19:38 by mdalloli          #+#    #+#             */
/*   Updated: 2025/07/01 10:48:57 by francema         ###   ########.fr       */
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

static char	*get_oldpwd(void)
{
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		perror("cd");
	return (oldpwd);
}

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

	oldpwd = get_oldpwd();
	if (!oldpwd)
	{
		shell->last_exit_code = 1;
		return ;
	}
	if (!args[1])
	{
		home = getenv("HOME");
		if (!home)
		{
			ft_putendl_fd("cd: HOME not set", 2);
			free(oldpwd);
			shell->last_exit_code = 1;
			return ;
		}
		change_dir_and_update(shell, oldpwd, home);
		return ;
	}
	change_dir_and_update(shell, oldpwd, args[1]);
	ft_lstclear(&shell->env, free);
}
