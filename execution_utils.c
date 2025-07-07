/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:18:34 by mdalloli          #+#    #+#             */
/*   Updated: 2025/07/07 17:52:48 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_command_not_found(t_exec_unit *unit)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(unit->argv[0], STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
}

void	free_split(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

static char	*ft_strjoin3(const char *s1, const char *s2, const char *s3)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(s1, s2);
	if (!tmp)
		return (NULL);
	res = ft_strjoin(tmp, s3);
	free(tmp);
	return (res);
}

static char	*search_in_paths(char **paths, const char *cmd)
{
	char	*full_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin3(paths[i], "/", cmd);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}
char	*check_cmd(const char *cmd, t_mini *shell)
{
	if (!cmd || !cmd[0])
		return (NULL);
	if (!ft_strcmp(cmd, "."))
	{
		printf("bash: .: filename argument required\n");
		cleanup_shell(shell, 2);
	}
	else if (!ft_strcmp(cmd, ".."))
		return(NULL);
	else if (ft_strchr(cmd, '/'))
	{
		printf("minishell: %s: Is a directory\n", cmd);
		cleanup_shell(shell, 126);
	}
	return("esiste");
}

char	*get_path_command(t_mini *shell, const char *cmd)
{
	char	**paths;
	char	*full_path;
	char	*path_var;

	if (!check_cmd(cmd, shell))
		return (NULL);
	path_var = get_env_value(shell, "PATH");
	if (!path_var)
		return (NULL);
	paths = ft_split(path_var, ':');
	if (!paths)
		return (NULL);
	full_path = search_in_paths(paths, cmd);
	free_split(paths);
	return (full_path);
}
