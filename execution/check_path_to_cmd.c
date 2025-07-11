/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path_to_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 23:17:15 by francema          #+#    #+#             */
/*   Updated: 2025/07/11 23:17:59 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*search_in_paths(char **paths, const char *cmd)
{
	char	*full_path;
	int		i;

	i = 0;
	if (ft_strchr(cmd, '/'))
		return ((char *)cmd);
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], "/");
		if (!full_path)
			return (NULL);
		full_path = ft_strjoin_free(full_path, (char *)cmd);
		if (!full_path)
			return (NULL);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

int	is_valid_exec_path(const char *cmd)
{
	struct stat	sb;

	if (access(cmd, X_OK) != 0)
		return (0);
	if (stat(cmd, &sb) != 0)
		return (0);
	if (S_ISDIR(sb.st_mode))
		return (0);
	return (1);
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
		return (NULL);
	else if (ft_strchr(cmd, '/'))
	{
		if (!is_valid_exec_path(cmd))
		{
			printf("minishell: %s: Is a directory or not executable\n", cmd);
			cleanup_shell(shell, 126);
		}
		return ("esiste");
	}
	return ("esiste");
}

char	*get_path_command(t_mini *shell, const char *cmd)
{
	char	**paths;
	char	*full_path;
	char	*path_var;

	if (ft_strchr(cmd, '/') || ft_strchr(cmd, '.'))
	{
		if (!check_cmd(cmd, shell))
			return (NULL);
	}
	if (cmd[0] == '\0')
		return (NULL);
	path_var = get_env_value(shell, "PATH");
	if (!path_var)
	{
		if (!check_cmd(cmd, shell))
			return (NULL);
		return (NULL);
	}
	paths = ft_split(path_var, ':');
	if (!paths)
		cleanup_shell(shell, 69);
	full_path = search_in_paths(paths, cmd);
	free_mat(paths);
	return (full_path);
}
