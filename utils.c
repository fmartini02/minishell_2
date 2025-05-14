#include "minishell.h"

/*Ritorna 1 se la stringa e' composta solo da spazi o tab*/
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

/*Se c e' uno dei caratteri non ammessi ritorna falso*/
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
