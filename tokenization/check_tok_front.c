/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tok_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 12:28:00 by francema          #+#    #+#             */
/*   Updated: 2025/07/04 16:35:31 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_var_value(t_mini *shell, size_t *i)
{
	char		*var_name;
	char		*var_value;
	int			end;
	int			start;
	t_tok_lst	*curr_node;

	start = get_doll_indx(shell->input, *i) + 1;
	end = start;
	curr_node = last_token(shell->tok_input);
	while (shell->input[end]
		&& !ft_ispecial_char(shell->input[end]))
		end++;
	var_name = ft_substr(shell->input, start, end - start);
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

// static void	check_var_front_utils(t_mini *shell, t_tok_lst *prev_node)
// {
// 	t_tok_lst	*new_node;
// 	char		*tmp;

// 	new_node = last_token(shell->tok_input);
// 	tmp = ft_strdup(new_node->content);
// 	if (!tmp)
// 		ft_fatal_memerr(shell);
// 	prev_node->content = ft_strjoin_free(prev_node->content, tmp);
// 	free(new_node->content);
// 	free(new_node);
// 	prev_node->next = NULL;
// }

int	dollar_part(t_mini *shell, size_t *i, t_tok_lst **curr_node)
{
	char	*var_value;

	var_value = get_var_value(shell, i);
	if (!var_value)
		return (VAR_NOT_FOUND);
	else if (var_value[ft_strlen(var_value) - 1] == ' ')
		return (EXIT_SUCCESS);
	*curr_node = last_token(shell->tok_input);
	if (shell->input[(*i) - 1] == ' ')
		return (IS_SPACE);
	return (EXIT_FAILURE);
}

void	update_nodes(t_mini *shell, t_tok_lst **last, t_tok_lst **curr)
{
	*last = last_token(shell->tok_input);
	(*curr)->content = ft_strjoin_free((*curr)->content,
			(*last)->content);
	if (last && (*last)->content)
	{
		free((*last)->content);
		free(*last);
	}
	if (*curr)
		(*curr)->next = NULL;
}

int	check_tok_front(t_mini *shell, size_t *i)
{
	int			return_value;
	t_tok_lst	*curr_node;
	t_tok_lst	*last_node;

	return_value = EXIT_SUCCESS;
	last_node = NULL;
	curr_node = last_token(shell->tok_input);
	if (shell->input[*i] == '$' && curr_node->type == DOLLAR)
		return (dollar_part(shell, i, &curr_node));
	if (shell->input[*i] == '\'')
		return_value = single_quotes_case(shell, NULL, i);
	else if (shell->input[*i] == '"')
		return_value = double_quotes_case(shell, NULL, i);
	else if (!is_word_delimiter(shell->input[*i]) && shell->input[*i] != ' ')
		return_value = word_case(shell, NULL, i);
	if (return_value == EXIT_FAILURE)
		return (EXIT_FAILURE);
	update_nodes(shell, &last_node, &curr_node);
	return (SUCCESS);
}
