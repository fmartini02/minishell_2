/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tok_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 12:12:13 by francema          #+#    #+#             */
/*   Updated: 2025/06/26 16:18:05 by francema         ###   ########.fr       */
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

int	check_tok_back_words(t_mini *shell, char *var_value, size_t *i)
{
	t_tok_lst	*prev_node;
	t_tok_lst	*curr_node;

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
		if (single_quotes_case(shell, NULL, i) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		curr_node = last_token(shell->tok_input);
		var_value = curr_node->content;
		prev_node->content = ft_strjoin_free(prev_node->content, var_value);
	}
	if (curr_node && curr_node->content)
	{
		free(curr_node->content);
		free(curr_node);
	}
	prev_node->next = NULL;
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
	return(free(var_name), VAR_NOT_FOUND);
}

/*per input come: "qualcosa"$var e var contiene una stringa senza spazzi all'inizio*/
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
		if (check_tok_back_words(shell, var_value, i) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
