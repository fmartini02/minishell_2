/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tok_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 12:28:00 by francema          #+#    #+#             */
/*   Updated: 2025/06/20 13:16:48 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	check_tok_front(t_mini *shell, size_t *i)
{
	int			return_value;
	t_tok_lst	*prev_node;
	char		*var_value;

	return_value = EXIT_SUCCESS;
	var_value = get_var_value(shell);
	if (!var_value)
		return(VAR_NOT_FOUND);
	else if (var_value[ft_strlen(var_value) - 1] == ' ')
		return (EXIT_SUCCESS);
	prev_node = last_token(shell->tok_input);
	if (shell->input[(*i) - 1] == ' ')
		return(IS_SPACE);
	if (shell->input[*i] == '\'')
		return_value = single_quotes_case(shell, NULL, i);
	else if (shell->input[*i] == '"')
		return_value = double_quotes_case(shell, NULL, i);
	if (return_value == EXIT_SUCCESS)
		check_var_front_utils(shell, prev_node);
	return (SUCCESS);
}
