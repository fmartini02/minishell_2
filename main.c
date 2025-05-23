/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:30:45 by francema          #+#    #+#             */
/*   Updated: 2025/05/21 15:23:17 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t sig_code = 0;


/* Processa il comando digitato:
Aggiunge alla history, tokenizza, analizza i simboli speciali
ed esegue camandi (env, pwd, exit)*/
void	parsing(t_mini *shell)
{
	add_history(shell->input);
	tokenize_input(shell);
	expand_wildcards(shell);
	ast_init(shell);
	if (!ft_strcmp(shell->input, "env"))
		ft_env(shell);
	else if (!ft_strcmp(shell->input, "pwd"))
		ft_pwd(shell);
	else if (!ft_strcmp(shell->input, "exit"))
		ft_exit(shell, NULL);
	else if (!ft_strcmp(shell->input, "echo"))
		ft_echo(shell);
	else if (!ft_strcmp(shell->input, "cd"))
		ft_cd(shell);
	else if (!ft_strcmp(shell->input, "export"))
		ft_export(shell); //da implementare
	else if (!ft_strcmp(shell->input, "unset"))
		ft_unset(shell); //da implementare
	free(shell->input);
}

/* Inizializzazione ambiente
Converte envp in una lista collegata (t_list) per una gestione presonallizata dell'ambiente*/
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
			if (shell.input[0] != '\0' || !is_all_spaces(shell.input))
				continue ;
			if (sig_code == SIGINT)
				sig_code = 0;
			else
				parsing(&shell);
			free(prompt);
		}
	}
}
