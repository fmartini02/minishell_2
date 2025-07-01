/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tok_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalloli <mdalloli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 12:12:13 by francema          #+#    #+#             */
/*   Updated: 2025/07/01 18:44:54 by mdalloli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	merge_tokens(char *var_value, char *var_name, t_mini *shell, int *j)
{
	char		*tmp;
	t_tok_lst	*head;

	head = shell->tok_input;
	shell->tok_input = last_token(head);
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
		return (free(tmp), ft_fatal_memerr(shell));
	free(tmp);
	*j += ft_strlen_till_space(var_value, *j);
	shell->tok_input = head;
}

t_tok_lst	*update_node(t_mini *shell, size_t *i, int type)
{
	t_tok_lst	*last_node;
	t_tok_lst	*curr_node;

	last_node = NULL;
	curr_node = last_token(shell->tok_input);
	if (type == DOUBLE_QUOTES)
	{
		if (double_quotes_case(shell, NULL, i) == EXIT_FAILURE)
			return (NULL);
	}
	else if (type == SINGLE_QUOTES)
	{
		if (single_quotes_case(shell, NULL, i) == EXIT_FAILURE)
			return (NULL);
	}
	last_node = last_token(shell->tok_input);
	curr_node->content = ft_strjoin_free(curr_node->content,
			last_node->content);
	curr_node->type = DOUBLE_QUOTES;
	if (last_node && last_node->content)
	{
		free(last_node->content);
		free(last_node);
	}
	return (curr_node);
}

int	check_tok_back_words(t_mini *shell, size_t *i)
{
	t_tok_lst	*curr_node;
	t_tok_lst	*last_node;

	curr_node = NULL;
	if (shell->input[*i] == '"')
		curr_node = update_node(shell, i, DOUBLE_QUOTES);
	else if (shell->input[*i] == '\'')
		curr_node = update_node(shell, i, SINGLE_QUOTES);
	if (curr_node)
		curr_node->next = NULL;
	last_node = last_token(shell->tok_input);
	last_node = curr_node;
	return (EXIT_SUCCESS);
}

int	check_tok_back_dollar(t_mini *shell, size_t *i, char *var_value)
{
	char	*var_name;
	int		j;

	var_name = get_var_name(shell->input, var_value, i, shell);
	if (!var_name)
		ft_fatal_memerr(shell);
	j = 0;
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
	return (free(var_name), VAR_NOT_FOUND);
}

/*per input come: "qualcosa"$var e
var contiene una stringa senza spazzi all'inizio*/
int	check_tok_back(t_mini *shell, size_t *i, bool is_dollar)
{
	char	*var_value;

	var_value = NULL;
	if (is_dollar)
	{
		var_value = ft_dollar_case(shell, shell->input, i);
		return (check_tok_back_dollar(shell, i, var_value));
	}
	else
	{
		if (check_tok_back_words(shell, i) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
