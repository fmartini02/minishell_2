/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 13:41:27 by mdalloli          #+#    #+#             */
/*   Updated: 2025/07/15 12:03:08 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	handle_missing_home(char *home, t_mini *shell)
{
	ft_putendl_fd("cd: HOME not set", 2);
	shell->last_exit_code = 1;
	free(home);
}

static void	cd_to_home(t_mini *shell, char **oldpwd)
{
	char	*home;
	size_t	i;

	i = 0;
	home = ft_dollar_case(shell, "$HOME", &i);
	if (!home || !home[0])
		return (handle_missing_home(home, shell));
	if (!*oldpwd)
		*oldpwd = ft_strdup("");
	change_dir_and_update(shell, *oldpwd, home);
	free(home);
}

static void	cd_to_path(t_mini *shell, char **oldpwd, char *path)
{
	if (!*oldpwd)
		*oldpwd = ft_strdup("");
	change_dir_and_update(shell, *oldpwd, path);
}

void	ft_cd(char **args, t_mini *shell)
{
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (!args[1])
		cd_to_home(shell, &oldpwd);
	else
		cd_to_path(shell, &oldpwd, args[1]);
	if (oldpwd)
		free(oldpwd);
}
