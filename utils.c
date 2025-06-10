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
