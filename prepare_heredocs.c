/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_heredocs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:11:11 by mdalloli          #+#    #+#             */
/*   Updated: 2025/07/10 18:05:38 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// minishell.h

extern volatile sig_atomic_t	g_sig_code;

/* static void	fill_heredoc_content(int write_fd, const char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(write_fd, line, ft_strlen(line));
		write(write_fd, "\n", 1);
		free(line);
	}
}

static void	setup_heredoc_pipe(t_redirection *redir)
{
	int	pipefd[2];

	if (pipe(pipefd) == -1)
		exit(1);
	fill_heredoc_content(pipefd[1], redir->target);
	close(pipefd[1]);
	redir->heredoc_fd = pipefd[0];
}

static void	process_cmd_heredocs(t_cmd_info *cmd)
{
	t_redirection	*redir;

	if (!cmd)
		return ;
	redir = cmd->redirections;
	while (redir)
	{
		if (redir->type == REDIR_HEREDOC)
			setup_heredoc_pipe(redir);
		redir = redir->next;
	}
}

void	prepare_heredocs(t_ast_node *ast)
{
	t_cmd_info	*cmd;

	if (!ast)
		return ;
	if (ast->type == NODE_PIPELINE)
	{
		prepare_heredocs(ast->left);
		prepare_heredocs(ast->right);
	}
	else if (ast->type == NODE_CMD)
	{
		cmd = (t_cmd_info *)ast->content;
		if (cmd)
			process_cmd_heredocs(cmd);
	}
} */


char	*add_var(char *line, size_t *i, char *to_print, t_mini *shell)
{
	char	*tmp;

	tmp = ft_dollar_case(shell, line, i);
	if (!tmp)
		ft_fatal_memerr(shell);
	to_print = ft_strjoin_free(to_print, tmp);
	free(tmp);
	return (to_print);
}

void	here_doc_doll_expansion(int write_fd, char *line, t_mini *shell)
{
	size_t	i;
	size_t	start;
	char	*tmp;
	char	*to_print;

	i = 0;
	start = 0;
	tmp = NULL;
	to_print = NULL;
	while (line[i])
	{
		while (line[i] && line[i] != ' ' && line[i] != '$')
		{
			if (line[i] == '\'')
			{
				i++;
				while (line[i] && line[i] != '\'')
				{
					if (line[i] == '$')
					{
						tmp = ft_substr(line, start, i - start);
						if (!tmp)
							ft_fatal_memerr(shell);
						to_print = ft_strjoin_free(to_print, tmp);
						free(tmp);
						to_print = add_var(line, &i, to_print, shell);
						start = i;
					}
					i++;
				}
				break ;
			}
			else if (line[i] == '"')
			{
				i++;
				while (line[i] && line[i] !='"')
				{
					if (line[i] == '$')
					{
						tmp = ft_substr(line, start, i - start);
						if (!tmp)
							ft_fatal_memerr(shell);
						to_print = ft_strjoin_free(to_print, tmp);
						free(tmp);
						to_print = add_var(line, &i, to_print, shell);
						start = i;
					}
					i++;
				}
			}
			i++;
		}
		if (line[i] != '$')
		{
			tmp = ft_substr(line, start, i - start);
			if (!tmp)
				ft_fatal_memerr(shell);
			to_print = ft_strjoin_free(to_print, tmp);
			if (!to_print)
				ft_fatal_memerr(shell);
		}
		start = i;
		if (line[i] == '$')
			to_print = add_var(line, &i, to_print, shell);
		if (tmp)
			free(tmp);
	}
	write(write_fd, to_print, ft_strlen(to_print));
	write(write_fd, "\n", 1);
	free(line);
	free(to_print);
}

char	*remove_quotes(const char *str)
{
	char	*new_str;
	int		i = 0, j = 0;
	size_t	len;

	if (!str)
		return (NULL);
	len = strlen(str);
	new_str = malloc(len + 1);
	if (!new_str)
		return (NULL);
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '"')
			new_str[j++] = str[i];
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}


static int	heredoc_read_loop(int write_fd, char *delimiter,
	struct sigaction *old_sa, t_mini *shell)
{
	char	*line;
	bool	doll_exp;
	char	*tmp;

	doll_exp = true;
	tmp = NULL;
	if (ft_strchr(delimiter, '\'') || ft_strchr(delimiter, '"'))
	{
		doll_exp = false;
		tmp = remove_quotes(delimiter);
		delimiter = tmp;
	}
	while (1)
	{
		line = readline("> ");
		if (g_sig_code == 130)
			return (free(line), sigaction_return(old_sa, -1));
		if (!line)
			return (write_ctrld(delimiter), sigaction_return(old_sa, -1));
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		if (!doll_exp)
		{
			write(write_fd, line, strlen(line));
			write(write_fd, "\n", 1);
			free(line);
		}
		if (doll_exp)
		{
			here_doc_doll_expansion(write_fd, line, shell);
		}
	}
	if (tmp)
		free(tmp);
	return (sigaction_return(old_sa, 0));
}

static int	fill_heredoc_content(int write_fd, char *delimiter, t_mini *shell)
{
	struct sigaction	sa;
	struct sigaction	old_sa;

	g_sig_code = 0;
	sa.sa_handler = heredoc_sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, &old_sa);
	return (heredoc_read_loop(write_fd, delimiter, &old_sa, shell));
}

static int	setup_heredoc_pipe(t_redirection *redir, t_mini *shell)
{
	int	pipefd[2];

	if (pipe(pipefd) == -1)
	{
		cleanup_shell(shell, -1);
		return (-1);
	}
	if (fill_heredoc_content(pipefd[1], redir->target, shell) < 0)
	{
		close(pipefd[1]);
		close(pipefd[0]);
		return (-1);
	}
	close(pipefd[1]);
	redir->heredoc_fd = pipefd[0];
	return (0);
}

static int	process_cmd_heredocs(t_cmd_info *cmd, t_mini *shell)
{
	t_redirection	*redir;

	if (!cmd)
		return (0);
	redir = cmd->redirections;
	while (redir)
	{
		if (redir->type == REDIR_HEREDOC)
			if (setup_heredoc_pipe(redir, shell) < 0)
				return (-1);
		redir = redir->next;
	}
	return (0);
}

int	prepare_heredocs(t_ast_node *ast, t_mini *shell)
{
	t_cmd_info	*cmd;
	int			ret;

	ret = 0;
	if (!ast)
		return (0);
	if (ast->type == NODE_PIPELINE)
	{
		if (prepare_heredocs(ast->left, shell) < 0)
			return (-1);
		if (prepare_heredocs(ast->right, shell) < 0)
			return (-1);
	}
	else if (ast->type == NODE_CMD)
	{
		cmd = (t_cmd_info *)ast->content;
		if (cmd)
			ret = process_cmd_heredocs(cmd, shell);
	}
	return (ret);
}
