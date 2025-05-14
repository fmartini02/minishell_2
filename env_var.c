#include "minishell.h"

/*Rstituisce il valore associato a una variabile d'ambiente */
char	*get_env_value(t_mini *shell, const char *var_name)
{
	t_list	*env_list;
	char	*entry;
	size_t	key_len;

	env_list = shell->env;
	key_len = ft_strlen(var_name);
	while (env_list)
	{
		entry = (char *)env_list->content;
		if (ft_strncmp(entry, var_name, key_len) == 0 && entry[key_len] == '=')
			return (entry + key_len + 1);
		env_list = env_list->next;
	}
	return (NULL);
}

/* Gestisce il caso speciale $?
Restituisce la stringa contenente il valore del last_exit_code*/
static char	*expand_exit_code(t_mini *shell, size_t *i)
{
	char	*value;
	char	*result;

	value = ft_itoa(shell->last_exit_code);
	result = ft_strdup(value);
	free(value);
	*i += 2;
	return (result);
}

/* Estrae il nome della variabile da una stringa dopo il simbolo '$*/
static char	*extract_var_name(char *str, size_t start, size_t *end)
{
	size_t	j;

	j = start;
	while (str[j] && !ft_ispecial_char(str[j]))
		j++;
	*end = j;
	return (ft_substr(str, start, j - start));
}

/* Espande una variabile d'ambiente in formato '$VAR' o '$?'
Modifica *i per spostare l'indice oltre la variabile espansa*/
void	dollar_case(t_mini *shell, char *str, size_t *i)
{
	size_t	start;
	size_t	j;
	char	*var_name;
	char	*var_value;

	start = *i + 1;
	if (str[*i + 1] == '?')
		return (expand_exit_code(shell, i));
	var_name = extract_var_name(str, start, &j);
	if (!var_name)
		return (NULL);
	var_value = get_env_value(shell, var_name);
	free(var_name);
	*i = j;
	if (!var_value)
		return (NULL);
	return (ft_strdup(var_value));
}
