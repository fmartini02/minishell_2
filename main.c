/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalloli <mdalloli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:30:45 by francema          #+#    #+#             */
/*   Updated: 2025/06/28 12:25:40 by mdalloli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t sig_code = 0;

/* Process of the command */
void	parsing(t_mini *shell)
{
	if (!tokenize_input(shell))
		return ;
	//print_tok_lst(shell->tok_input);
	//expand_wildcards(shell);
	ast_init(shell);
	//print_ast(shell->ast_root, 0);
	execute_ast(shell->ast_root, shell);
	//free(shell->input);
}

/* Initializes a linked list of environment variabiles */
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

int	main(int ac, char **av, char **envp)
{
	t_mini	shell;
	char	*input;
	char	*prompt;
	int		is_interactive;

	(void)av;
	(void)ac;
	is_interactive = isatty(STDIN_FILENO);
	setup_sig_handler(is_interactive);
	rl_catch_signals = 0;
	shell.envp = envp;
	shell.env = init_env(envp);
	shell.last_exit_code = 0;
	shell.input = NULL;
	shell.cmd_info = NULL;
	shell.tok_input = NULL;
	shell.ast_root = NULL;
	shell.err_print = false;
	if (!shell.env)
		ft_fatal_memerr(&shell);
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
		while(1)
		{
			prompt = get_prompt();
			if (!prompt)
				prompt = ft_strdup("minishell$ ");
			sig_code = -42; // <--- SEI AL PROMPT!
			shell.input = readline(prompt);
			sig_code = 0;
			if (!shell.input)
				ctrl_d_case(&shell);
			/* if (sig_code == SIGINT || sig_code == SIGQUIT)
			{
				sig_code = 0;
				free(prompt);
				free(shell.input);
				continue;
			} */
			if (shell.input[0] == '\0' || is_all_spaces(shell.input))
			{
				free(shell.input);
				free(prompt);
				continue ;
			}
			add_history(shell.input);
			parsing(&shell);
			shell.err_print = false;
			free(prompt);
			free(shell.input);
		}
	}
}
