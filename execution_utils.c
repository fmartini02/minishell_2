/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:18:34 by mdalloli          #+#    #+#             */
/*   Updated: 2025/07/10 21:33:17 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_command_not_found(t_exec_unit *unit)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(unit->argv[0], STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
}

// static char	*ft_strjoin3(const char *s1, const char *s2, const char *s3)
// {
// 	char	*tmp;
// 	char	*res;

// 	tmp = ft_strjoin(s1, s2);
// 	if (!tmp)
// 		return (NULL);
// 	res = ft_strjoin(tmp, s3);
// 	free(tmp);
// 	return (res);
// }

static char	*search_in_paths(char **paths, const char *cmd)
{
	char	*full_path;
	int		i;

	i = 0;
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
		return (ft_strdup(cmd));
	}
	return (ft_strdup("esiste"));
}

char	*get_path_command(t_mini *shell, const char *cmd)
{
	char	**paths;
	char	*full_path;
	char	*path_var;

	if (ft_strchr(cmd, '/'))
		return(check_cmd(cmd, shell));
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
