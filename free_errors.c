#include "minishell.h"

/* Libera una lista collegata di strutture t_cmd_info
void	ft_free_cmd_info(t_cmd_info *cmd_info)
{
	int			i;
	t_cmd_info	*next;

	while (cmd_info)
	{
		i = 0;
		free(cmd_info->cmd_name);
		if (cmd_info->cmd_args)
		{
			while (cmd_info->cmd_args[i])
			{
				free(cmd_info->cmd_args[i]);
				i++;
			}
			free(cmd_info->cmd_args);
		}
		next = cmd_info->next;
		free(cmd_info);
		cmd_info = next;
	}
}*/

/* Handles a fatal memory allocation error.
Frees all shell resources, prints an error message
and terminates the program */
void	ft_fatal_memerr(t_mini *shell)
{
	ft_putstr_fd("Error: malloc failure \n", 2);
	free(shell->input);
	ft_lstclear(&shell->env, free);
	free_tok_lst(&shell->tok_input);
	//ft_free_cmd_info(shell->cmd_info);
	exit(EXIT_FAILURE);
}

/* Frees all memory associated with a t_exec_unit structure.
This includes the argument vector (argv) and the structure itself.
If the unit is NULL, the function does nothing.*/
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
