/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:30:45 by francema          #+#    #+#             */
/*   Updated: 2025/05/28 15:49:07 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t sig_code = 0;


/* Processa il comando digitato:
Aggiunge alla history, tokenizza, analizza i simboli speciali
ed esegue camandi (env, pwd, exit)*/
void	parsing(t_mini *shell)
{
	if (!tokenize_input(shell))
		return ;
	// ft_print_list(shell->tok_input, 's');
	//expand_wildcards(shell);
	ast_init(shell);
	if (!ft_strcmp(shell->cmd_info->cmd_name, "env"))
		ft_env(shell);
	else if (!ft_strcmp(shell->cmd_info->cmd_name, "pwd"))
		ft_pwd(shell);
	else if (!ft_strcmp(shell->cmd_info->cmd_name, "exit"))
		ft_exit(shell, NULL);
	else if (!ft_strcmp(shell->cmd_info->cmd_name, "echo"))
		ft_echo(shell);
	else if (!ft_strcmp(shell->cmd_info->cmd_name, "cd"))
		ft_cd(shell);
	else if (!ft_strcmp(shell->cmd_info->cmd_name, "export"))
		ft_export(shell);
	else if (!ft_strcmp(shell->cmd_info->cmd_name, "unset"))
		ft_unset(shell);
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
	shell.subshell_flag = 0;
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
		while(ac)
		{
			prompt = get_prompt();
			if (!prompt)
				prompt = ft_strdup("minishell$ ");
			shell.input = readline(prompt);
			if (!shell.input)
				ctrl_d_case(&shell);
			if (shell.input[0] == '\0' || is_all_spaces(shell.input))
				continue ;
			if (sig_code == SIGINT)
				sig_code = 0;
			else
			{
				add_history(shell.input);
				parsing(&shell);
			}
			free(prompt);
		}
	}
}
