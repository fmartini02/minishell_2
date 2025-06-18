#include "minishell.h"

static int	count_pipeline_commands(t_ast_node *cmd_list)
{
	int count = 0;
	while (cmd_list)
	{
		count++;
		cmd_list = cmd_list->next;
	}
	return count;
}

static bool input_redir_exists(t_redirection *r)
{
	while (r)
	{
		if (r->type == REDIR_INPUT || r->type == REDIR_HEREDOC)
			return true;
		r = r->next;
	}
	return false;
}

static bool output_redir_exists(t_redirection *r)
{
	while (r)
	{
		if (r->type == REDIR_OUTPUT || r->type == REDIR_APPEND)
			return true;
		r = r->next;
	}
	return false;
}

static int	**create_pipes(int count)
{
	int	**pipes = malloc(sizeof(int *) * (count - 1));
	if (!pipes)
		return (NULL);
	for (int i = 0; i < count - 1; i++)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i] || pipe(pipes[i]) < 0)
			return (NULL);
	}
	return (pipes);
}
static void	close_all_pipes(int **pipes, int count)
{
	int i =  0;

	while (i < count - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

static void	free_pipes(int **pipes, int count)
{
	for (int i = 0; i < count - 1; i++)
		free(pipes[i]);
	free(pipes);
}

static void	child_pipeline(t_ast_node *node, t_mini *shell, int **pipes, int i, int count)
{
	t_exec_unit	*unit = extract_exec_unit(node);
	if (!unit)
		exit(1);

	// Configura STDIN se non c'è redirezione e non è il primo comando
	if (i > 0 && !input_redir_exists(unit->redirs))
	{
		if (dup2(pipes[i - 1][0], STDIN_FILENO) < 0)
		{
			perror("dup2 stdin failed");
			exit(1);
		}
	}

	// Configura STDOUT se non c'è redirezione e non è l'ultimo comando
	if (i < count - 1 && !output_redir_exists(unit->redirs))
	{
		if (dup2(pipes[i][1], STDOUT_FILENO) < 0)
		{
			perror("dup2 stdout failed");
			exit(1);
		}
	}

	// 🔥 Chiudi TUTTE le pipe nel figlio, dopo dup2
	for (int j = 0; j < count - 1; j++)
	{
		close(pipes[j][0]);
		close(pipes[j][1]);
	}

	// Applica redirezioni specifiche
	if (apply_redirections(unit, shell) != 0)
		exit(1);

	// Built-in o comando esterno
	if (is_builtin(unit->argv[0]))
		exit(execute_builtin(unit, shell));

	execvp(unit->argv[0], unit->argv);
	perror("execvp failed");
	exit(127);
}


void execute_pipeline(t_ast_node *cmd_list, t_mini *shell)
{
	int count = count_pipeline_commands(cmd_list);
	if (count == 0)
		return;
	int **pipes = NULL;
	if (count > 1)
	{
		pipes = create_pipes(count);
		if (!pipes)
		{
			perror("pipe allocation");
			exit(1);
		}
	}
	pid_t *pids = malloc(sizeof(pid_t) * count);
	if (!pids)
	{
		perror("malloc pids");
		if (pipes)
			free_pipes(pipes, count);
		exit(1);
	}
	t_ast_node *curr = cmd_list;
	for (int i = 0; i < count && curr; i++)
	{
		pids[i] = fork();
		if (pids[i] < 0)
		{
			perror("fork failed");
			free(pids);
			if (pipes)
				free_pipes(pipes, count);
			exit(1);
		}
		else if (pids[i] == 0)
		{
			child_pipeline(curr, shell, pipes, i, count);
			exit(1); // Should never reach here
		}
		curr = curr->next;
	}
	if (pipes)
	{
		for (int i = 0; i < count - 1; i++)
		{
			close(pipes[i][0]);
			close(pipes[i][1]);
		}
		free_pipes(pipes, count);
	}
	int status = 0;
	for (int i = 0; i < count; i++)
		waitpid(pids[i], &status, 0);

	shell->last_exit_code = WEXITSTATUS(status);
	free(pids);
}
