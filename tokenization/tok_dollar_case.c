/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_dollar_case.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:13:27 by francema          #+#    #+#             */
/*   Updated: 2025/07/04 16:42:27 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*libera tutto ciò che è stato allocato prima dell'errore*/
void	append_nodes_err(char *tmp, char *var_name,
		char *var_value, t_tok_lst *new_node)
{
	if (tmp)
		free(tmp);
	if (var_name)
		free(var_name);
	if (var_value)
		free(var_value);
	if (new_node)
		free(new_node);
}

/*crea il nodo mettendo dentro la prima "parola" incontrata
dentro la variabile*/
static void	append_var_utils(t_mini *shell, char *var_value, char *var_name,
	int j)
{
	char		*tmp;
	t_tok_lst	*new_node;

	tmp = ft_substr(var_value, j, ft_strlen_till_space(var_value, j));
	new_node = new_tok_lst(tmp, DOLLAR, var_name);
	if (!new_node || !tmp)
	{
		append_nodes_err(tmp, var_name, var_value, new_node);
		ft_fatal_memerr(shell);
	}
	add_back_tok_lst(&shell->tok_input, new_node);
	if (!shell->tok_input)
	{
		append_nodes_err(tmp, var_name, var_value, new_node);
		ft_fatal_memerr(shell);
	}
}

/*accoda alla lista dei token il contenuto della var
(tokenizzandolo se sono presenti degli sapzzi)*/
int	append_var(char *var_value, char *var_name, t_mini *shell, int j)
{
	t_tok_lst	*head;

	j = ft_skip_spaces(var_value, j);
	head = shell->tok_input;
	shell->tok_input = last_token(shell->tok_input);
	while (var_value[j])
	{
		append_var_utils(shell, var_value, var_name, j);
		if (shell->tok_input->next)
			shell->tok_input = shell->tok_input->next;
		shell->tok_input->type = DOLLAR;
		shell->tok_input->tok_name = var_name;
		j += ft_strlen_till_space(var_value, j);
		j = ft_skip_spaces(var_value, j);
	}
	shell->tok_input = head;
	return (EXIT_SUCCESS);
}

bool	should_print_doll_char(char *s, size_t *i)
{
	char	*chars;
	int		j;

	chars = "!\"%&'()*+,-./:;<=>@[\\]^`{|}~ ";
	j = 0;
	while (chars[j])
	{
		if (s[*i + 1] == chars[j])
		{
			if (s[*i + 1] == '\'' || s[*i + 1] == '"')
				return (*i += 1, false);
			return (true);
		}
		j++;
	}
	if (s[*i + 1] == '\0')
		return (true);
	return (false);
}

int	doll_special_cases(t_mini *shell, size_t *i)
{
	t_tok_lst	*node;
	char		*content;

	node = NULL;
	content = NULL;
	if (should_print_doll_char(shell->input, i))
	{
		content = ft_strdup("$");
		if (!content)
			ft_fatal_memerr(shell);
		node = new_tok_lst(content, WORD, NULL);
		if (!node)
		{
			free(content);
			ft_fatal_memerr(shell);
		}
		add_back_tok_lst(&shell->tok_input, node);
		return (*i += 1, EXIT_SUCCESS);
	}
	if (!should_print_doll_char(shell->input, i))
	{
		if (shell->input[*i] == '"' || shell->input[*i] =='\'')
			return (EXIT_FAILURE);
	}
	return (EXIT_FAILURE);
}
/*aggiunge alla t_tok_lst il contenuto della <$var>*/
int	tok_dollar_case(t_mini *shell, size_t *i, char *content)
{
	char		*s;
	char		*var_name;

	s = shell->input;
	if (doll_special_cases(shell, i) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	if (doll_special_cases(shell, i) == EXIT_FAILURE)
	{
		if (s[*i] == '"' || s[*i] == '\'')
			return (EXIT_SUCCESS);
	}
	content = ft_dollar_case(shell, s, i);
	if (!content)
		return (2);
	var_name = get_var_name(s, content, i, shell);
	if (!var_name)
		ft_fatal_memerr(shell);
	append_var(content, var_name, shell, 0);
	if (content)
	{
		free(content);
		content = NULL;
	}
	return (EXIT_SUCCESS);
}
