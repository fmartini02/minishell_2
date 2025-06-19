/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:00:22 by francema          #+#    #+#             */
/*   Updated: 2025/06/19 17:33:24 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	merge_tokens(char *var_value, char *var_name, t_mini *shell, int *j)
{
	char	*tmp;

	tmp = ft_substr(var_value, 0, ft_strlen_till_space(var_value, *j));
	if (!tmp)
	{
		ft_fatal_memerr(shell);
		return ;
	}
	shell->tok_input->content = ft_strjoin_free(shell->tok_input->content, tmp);
	shell->tok_input->type = DOLLAR;
	shell->tok_input->tok_name = var_name;
	if (!shell->tok_input->content)
	{
		free(tmp);
		ft_fatal_memerr(shell);
		return ;
	}
	free(tmp);
	*j += ft_strlen_till_space(var_value, *j);
}

/*per input come: "qualcosa"$var e var contiene una stringa senza spazzi all'inizio*/
int	check_var_back(t_mini *shell, size_t *i, bool is_dollar)
{
	char		*var_value;
	char		*var_name;
	t_tok_lst	*curr_node;
	t_tok_lst	*prev_node;
	int			j;

	j = 0;
	if (is_dollar)
	{
		var_name = ft_substr(shell->input, *i, ft_strlen_till_space(shell->input, *i));
		var_value = ft_dollar_case(shell, shell->input, i);
		if (var_value)
		{
			if (!ft_ispace(var_value[j]))
			{
				merge_tokens(var_value, var_name, shell, &j);
				return (append_var(var_value, var_name, shell, j));
			}
			else if (ft_ispace(var_value[j]))
				return (append_var(var_value, var_name, shell, j));
		}
		else
			return(free(var_name), 2);
	}
	else
	{
		prev_node = last_token(shell->tok_input);
		curr_node = NULL;
		if (shell->input[*i] == '"')
		{
			if (double_quotes_case(shell, NULL, i) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			curr_node = last_token(shell->tok_input);
			var_value = curr_node->content;
			prev_node->content = ft_strjoin_free(prev_node->content, var_value);
		}
		else if (shell->input[*i] == '\'')
		{
			if (double_quotes_case(shell, NULL, i) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			curr_node = last_token(shell->tok_input);
			var_value = curr_node->content;
			prev_node->content = ft_strjoin_free(prev_node->content, var_value);
		}
		free(curr_node->content);
		free(curr_node);
		prev_node->next = NULL;
	}
	return (EXIT_SUCCESS);
}

static char	*get_var_value(t_mini *shell)
{
	char		*var_name;
	char		*var_value;
	int			j;
	t_tok_lst	*curr_node;

	j = 1;
	curr_node = last_token(shell->tok_input);
	while (curr_node->tok_name[j]
			&& !ft_ispecial_char(curr_node->tok_name[j]))
		j++;
	var_name = ft_substr(curr_node->tok_name, 1, j-1);
	if (!var_name)
	{
		ft_fatal_memerr(shell);
		return (NULL);
	}
	var_value = get_env_value(shell, var_name);
	free(var_name);
	if (!var_value)
		return (NULL);
	return (var_value);
}

static void	check_var_front_utils(t_mini *shell, t_tok_lst *prev_node)
{
	t_tok_lst	*new_node;
	char		*tmp;

	new_node = last_token(shell->tok_input);
	tmp = ft_strdup(new_node->content);
	if (!tmp)
		ft_fatal_memerr(shell);
	prev_node->content = ft_strjoin_free(prev_node->content, tmp);
	free(new_node->content);
	free(new_node);
	prev_node->next = NULL;
}

int	check_var_front(t_mini *shell, size_t *i)
{
	int			return_value;
	t_tok_lst	*prev_node;
	char		*tmp;
	char		*var_value;

	return_value = EXIT_SUCCESS;
	var_value = get_var_value(shell);
	if (!var_value)
		return(2);// Variable not found
	else if (var_value[ft_strlen(var_value) - 1] == ' ')
		return (EXIT_SUCCESS);
	prev_node = last_token(shell->tok_input);
	if (shell->input[(*i) - 1] == ' ')
		return(69);
	if (shell->input[*i] == '\'')
		return_value = single_quotes_case(shell, NULL, i);
	else if (shell->input[*i] == '"')
		return_value = double_quotes_case(shell, NULL, i);
	if (return_value == EXIT_SUCCESS)
		check_var_front_utils(shell, prev_node);
	return (10);
}

/*gestisce quei token che vanno uniti se non ci sono spazzi con un focus specifico per il caso <"c"$var"d"> */
static void	pettish_tokens(t_mini *shell, char *s, size_t *i, int *return_value)
{
	t_tok_lst	*curr_tok;
	char		c;

	c = s[*i];
	curr_tok = last_token(shell->tok_input);
	if (curr_tok && curr_tok->type == DOLLAR && s[(*i) - 1] != ' ')//if the previus is a dollar token
	{
		*return_value =  check_var_front(shell, i);
		if(return_value == EXIT_FAILURE)
			return ;
	}
	if (*return_value == EXIT_SUCCESS)
	{
		if (c == '\'')
			*return_value = single_quotes_case(shell, NULL, i);
		else if (c == '"')
			*return_value = double_quotes_case(shell, NULL, i);
		else if (!is_special_char(c) && c != ' ')
			*return_value = word_case(shell, NULL, i);
	}
	if (s[*i] != ' ')
		*return_value = check_var_back(shell, i, true);
}

/* Restituisce un token applicando anche alcune espansioni <$var>*/
int	get_tok(t_mini *shell, char *s, size_t *i)
{
	char		*content;
	int			return_value;

	content = NULL;
	return_value = EXIT_SUCCESS;
	pettish_tokens(shell, s, i, &return_value);
	if (return_value == EXIT_FAILURE)
		return (return_value);
	if (s[*i] == '$')
		return_value  = tok_dollar_case(shell, i, content);
	else if (s[*i] == '*')
		return_value = wildcard_case(shell, content, i);
	else if (s[*i] == '(' || s[*i] == ')')
		return_value = subshell_case(shell, content, i);
	else if (s[*i] == '&')
		return_value = and_case(shell, content, i);
	else if (s[*i] == '|')
		return_value = pipe_char_case(shell, content, i);
	else if (s[*i] == '<' || s[*i] == '>')
		return_value = redi_case(shell, content, i);
	return (return_value);
}

/* Suddivide l'input(shell->input) in una lista di token(shell->tok_input) usando get_tok
Serve per dividere il comando in parole comprensibili alla shell*/
bool	tokenize_input(t_mini *shell)
{
	size_t		i;
	char		*s;
	int			return_value;

	i = 0;
	s = shell->input;
	i = ft_skip_spaces(s, i);
	shell->tok_input = NULL;
	return_value = EXIT_FAILURE;
	while (s[i])
	{
		return_value = get_tok(shell, s, &i);
		if (return_value == EXIT_FAILURE)
			return (false);
		else if (return_value == 2)//($var) doesn't exist
			continue ;
		i = ft_skip_spaces(s, i);
	}
	return (true);
}
