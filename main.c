/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:30:45 by francema          #+#    #+#             */
/*   Updated: 2025/05/12 17:45:12 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t sig_code = 0;

void	ft_env(t_mini *shell)
{
	t_list	*tmp;

	tmp = shell->env;
	ft_print_list(tmp, 's');
}

void	ft_pwd(t_mini *shell)
{
	char	*pwd;

	(void)shell;
	pwd = malloc(sizeof(char) * PATH_MAX);
	if (!pwd)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	if (!getcwd(pwd, PATH_MAX))
	{
		perror("getcwd");
		free(pwd);
		exit(EXIT_FAILURE);
	}
	ft_printf("%s\n", pwd);
	free(pwd);
}

char	*get_word(t_mini *shell, char *s, size_t *i, size_t len)
{
	char	*content;

	(void)shell;
	content = malloc(sizeof(char) * (len + 1));
	if (!content)
		return (NULL);
	len = 0;
	while(s[*i] && !ft_ispace(s[*i]))
		content[len++] = s[(*i)++];
	content[len] = '\0';
	return(content);
}

void	tokenize_input(t_mini *shell)
{
	size_t	i;
	size_t	len;
	char	*s;
	char	*content;
	t_list	*node;

	i = 0;
	s = shell->input;
	i = ft_skip_spaces(s, i);
	shell->tok_input = NULL;
	while (s[i])
	{
		len = ft_word_len(&s[i]);
		content = get_word(shell, s, &i, len);
		if (!content)
			ft_fatal_memerr(shell);
		node = ft_lstnew(content);
		if (!node)
			ft_fatal_memerr(shell);
		ft_lstadd_back(&shell->tok_input, node);
		i += ft_strlen_till_space(s, i);
		i = ft_skip_spaces(s, i);
	}
}


void	ft_init_cmd_info(t_mini *shell)
{
	size_t	i;
	char	*s;

	i = 0;
	s = shell->input;
	while(s[i])
	{
		/*if (s[i] == '\'')
			single_quotes_case(shell, &i);
		if (s[i] == '"')
			duble_quotes_case(shell, &i);
		if (s[i] == '$')
			dollar_case(shell, &i);
		if (s[i] == '<' || s[i] == '>')
			redi_case(shell, &i);
		if (s[i] == '|')
			pipe_char_case(shell, &i);
		if (s[i] == '&')
			ampersand_case(shell, &i);
		if (s[i] == '(')
			parentesis_case(shell, &i);
		if (s[i] == '*')
			wildcard_case(shell, &i);*/
		i++;
	}
}

void	parsing(t_mini *shell)
{
	add_history(shell->input);
	tokenize_input(shell);
	ft_print_list(shell->tok_input, 's');
	ft_init_cmd_info(shell);
	if (!ft_strcmp(shell->input, "env"))
		ft_env(shell);
	else if (!ft_strcmp(shell->input, "pwd"))
		ft_pwd(shell);
	else if (!ft_strcmp(shell->input, "exit"))
		ft_exit(shell, NULL);
	free(shell->input);
}

void	ctrl_d_case(t_mini *shell)
{
	free(shell->input);
	ft_lstclear(&shell->env, free);
	exit(0);
}

t_list	*init_env(char **env)
{
	t_list	*head;
	int		i;

	if (env[0])
		head = ft_lstnew((void *) ft_strdup(env[0]));
	else
		return(NULL);
	i = 1;
	while(env[i])
	{
		ft_lstadd_back(&head, ft_lstnew(ft_strdup(env[i])));
		i++;
	}
	return (head);
}

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		sig_code = SIGINT;
		write (STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	/*else if (sig == SIGQUIT)
	{
		sig_code = SIGQUIT;
		write (STDOUT_FILENO, "Quit (core dumped)\n", 19);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}*/
}

void	setup_sig_handler(int is_interactive)
{
	struct sigaction sa;
	struct sigaction ignore_sa;
	int i;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (!is_interactive)
		sa.sa_handler = SIG_DFL;
	else
	{
		sa.sa_handler = signal_handler;
		sigaction(SIGQUIT, &sa, NULL);
		sigaction(SIGINT, &sa, NULL);
		i = -1;
		while(++i < _NSIG)
		{
			if (i == SIGKILL || i == SIGSTOP || i == SIGINT)
				continue;
			ft_memset(&ignore_sa, 0, sizeof(ignore_sa));
			ignore_sa.sa_handler = SIG_IGN;
			sigaction(i, &ignore_sa, NULL);
		}
	}
}

int is_all_spaces(const char *str)
{
	while (*str)
	{
		if (*str != ' ' && *str != '\t')
			return (0);
		str++;
	}
	return (1);
}


int	main(int ac, char **av, char **envp)
{
	t_mini	shell;
	char	*input;
	char	*prompt;
	int		is_interactive;

	(void)av;
	is_interactive = isatty(STDIN_FILENO);
	setup_sig_handler(is_interactive);
	shell.envp = envp;
	shell.env = init_env(envp);

	if (!is_interactive)
	{
		input = get_next_line(0);
		while (input)
		{
			shell.input = ft_strdup(input);
			free(input);
		}
		parsing(&shell);
	}
	else
	{
		while(ac)
		{
			prompt = get_prompt();
			if (!prompt)
				prompt = ft_strdup("minishell$ ");
			shell.input = readline(prompt);
			if (!shell.input)
				ctrl_d_case(&shell);
			if (shell.input[0] != '\0' && !is_all_spaces(shell.input))
				add_history(shell.input);
			if (sig_code == SIGINT)
				sig_code = 0;
			else
				parsing(&shell);
			free(prompt);
		}
	}
}
