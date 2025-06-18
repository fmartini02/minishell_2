#include "minishell.h"

/*  Returns 1 if string consists only of spaces or tabs */
int	is_all_spaces(const char *str)
{
	while (*str)
	{
		if (*str != ' ' && *str != '\t')
			return (0);
		str++;
	}
	return (1);
}

/* If there is one of the characters not allowed it returns false */
bool	ft_ispecial_char(char c)
{
	if (c != '!' && c != '@' && c != '#' && c != '%' && c != '^' && c != '&'
		&& c != '*' && c != '(' && c != ')' && c != '-' && c != '+'
		&& c != '=' && c != '[' && c != ']' && c != '{' && c != '}'
		&& c != '\\' && c != '|' && c != ';' && c != ':' && c != '\''
		&& c != '"' && c != '<' && c != '>' && c != ',' && c != '.' && c != '?'
		&& c != '/' && c != '~' && c != '`' && c != '\0')
		return (false);
	return (true);
}

/* Checks if the given command is a built-in shell command */
bool	is_builtin(const char *cmd)
{
	return (ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0
		|| ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0);
}
