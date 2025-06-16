/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_dollar_case.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:13:27 by francema          #+#    #+#             */
/*   Updated: 2025/06/16 20:03:58 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	append_var(char *var_value, char *var_name, t_mini *shell, int j)
{
	char		*tmp;
	t_tok_lst	*new_node;

	while (var_value[j])
	{
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
		if (shell->tok_input->next)
			shell->tok_input= shell->tok_input->next;
		shell->tok_input->type = DOLLAR;
		shell->tok_input->tok_name = var_name;
		j += ft_strlen_till_space(var_value, j);
		j = ft_skip_spaces(var_value, j);
	}
	return (EXIT_SUCCESS);
}

int	tok_dollar_case(t_mini *shell, size_t *i, char *content)
{
	char		*s;
	char		*var_name;

	s = shell->input;
	var_name = ft_substr(s, *i, ft_strlen_till_space(shell->input, *i));
	//printf("var_name: %s\n", var_name);
	if (!var_name)
		ft_fatal_memerr(shell);
	content = ft_dollar_case(shell, s, i);
	if (!content)
		return (2);
	append_var(content, var_name, shell, 0);
	return (EXIT_SUCCESS);
}
