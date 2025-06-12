/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:30:45 by francema          #+#    #+#             */
/*   Updated: 2025/06/05 17:45:08 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t sig_code = 0;

bool	is_builtin(const char *cmd)
{
	return (ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0
		|| ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0);
}

int	execute_builtin(t_exec_unit *unit, t_mini *shell)
{
	char **args = unit->argv;

	if (!args || !args[0])
		return (1);
	if (ft_strcmp(args[0], "echo") == 0)
		ft_echo(shell);
	else if (ft_strcmp(args[0], "cd") == 0)
		ft_cd(shell);
	else if (ft_strcmp(args[0], "pwd") == 0)
		ft_pwd(shell);
	else if (ft_strcmp(args[0], "export") == 0)
		ft_export(shell);
	else if (ft_strcmp(args[0], "unset") == 0)
		ft_unset(shell);
	else if (ft_strcmp(args[0], "env") == 0)
		ft_env(shell);
	else if (ft_strcmp(args[0], "exit") == 0)
		ft_exit(shell, NULL);
	return (shell->last_exit_code);
}

void	free_exec_unit(t_exec_unit *unit)
{
	int	i;

	if (!unit)
		return ;
	i = 0;
	while (unit->argv[i])
	{
		free(unit->argv[i]);
		i++;
	}
	free(unit->argv);
	free(unit);
}

/* Extracts execution unit from a command AST node */
t_exec_unit	*extract_exec_unit(t_ast_node *node)
{
	t_cmd_info	*cmd;
	t_exec_unit	*unit;
	int			i;
	int			argc;
	
	if (!node || node->type != NODE_CMD)	// Check if node is valid and is a command node
		return (NULL);
	cmd = (t_cmd_info *)node->content;	// Get command info from node content
	if (!cmd || !cmd->cmd_args)
		return (NULL);
	unit = malloc(sizeof(t_exec_unit));		// Allocate memory for execution unit
	if (!unit)
		return (NULL);
	argc = 0;
	while (cmd->cmd_args[argc])				// Count number of arguments
		argc++;
	unit->argv = malloc(sizeof(char *) *(argc + 1));	// Allocate memory for argv for argv array
	if (!unit->argv)
	{
		free(unit);
		return (NULL);
	}
	i = 0;
	while (i < argc)		// Duplicate the arguments
	{
		unit->argv[i] = ft_strdup(cmd->cmd_args[i]);
		if (!unit->argv[i])
		{
			while (--i >= 0)	// In case of error: free
				free(unit->argv[i]);
			free(unit->argv);
			free(unit);
			return (NULL);
		}
		i++;
	}
	unit->argv[argc] = NULL;
	unit->redirs = cmd->redirections;	// Link redirection list (no need to duplicate here)
	return (unit);
}

void	execute_exec_unit(t_exec_unit *unit, t_mini *shell)
{
	pid_t	pid;
	int		status;

	if (!unit || !unit->argv || !unit->argv[0])
		return ;
	if (is_builtin(unit->argv[0])	// Esegui nel padre se è un built-in critico
		&& (ft_strcmp(unit->argv[0], "cd") == 0
			|| ft_strcmp(unit->argv[0], "export") == 0
			|| ft_strcmp(unit->argv[0], "unset") == 0
			|| ft_strcmp(unit->argv[0], "exit") == 0))
	{
		if (apply_redirections(shell) != 0)	// Applichiamo anche eventuali redirection nel padre, se necessario
		{
			shell->last_exit_code = 1;
			return ;
		}
		shell->last_exit_code = execute_builtin(unit, shell);
		return ;
	}
	pid = fork();	// Altrimenti: fork e poi execvp o built-in non critico
	if (pid == 0)
	{
		if (apply_redirections(shell) != 0)
			exit(1);
		if (is_builtin(unit->argv[0]))
			exit(execute_builtin(unit, shell));
		execvp(unit->argv[0], unit->argv);
		perror("execvp failed");
		exit(127);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			shell->last_exit_code = WEXITSTATUS(status);
	}
	else
	{
		perror("fork failed");
		shell->last_exit_code = 1;
	}
}

void	execute_ast(t_ast_node *node, t_mini *shell)
{
	t_exec_unit	*unit;

	if (!node)
		return ;
	if (node->type == NODE_CMD)
	{
		unit = extract_exec_unit(node);
		if (unit)
		{
			execute_exec_unit(unit, shell);
			free_exec_unit(unit);
		}
	}
	/* else if (node->type == NODE_PIPELINE)
	{
		// execute_pipeline
	} */
	else if (node->type == NODE_AND)
	{
		execute_ast(node->left, shell);
		if (shell->last_exit_code == 0)
			execute_ast(node->right, shell);
	}
	else if (node->type == NODE_OR)
	{
		execute_ast(node->left, shell);
		if (shell->last_exit_code != 0)
			execute_ast(node->right, shell);
	}
}

/* Process of the command */
void	parsing(t_mini *shell)
{
	if (!tokenize_input(shell))
		return ;
	//ft_print_list(shell->tok_input, 's');
	//expand_wildcards(shell);
	ast_init(shell);
	execute_ast(shell->ast_root, shell);
	print_ast(shell->ast_root, 0);
	free(shell->input);
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
		while(1)
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
				shell.subshell_flag = 0;
				shell.err_print = false;
			}
			free(prompt);
		}
	}
}
