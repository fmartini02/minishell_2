/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:10:17 by francema          #+#    #+#             */
/*   Updated: 2025/06/30 18:44:44 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tok_lst	*new_tok_lst(char *content, t_tok_type type, char *tok_name)
{
	t_tok_lst	*new_node;

	new_node = (t_tok_lst *)malloc(sizeof(t_tok_lst));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->type = type;
	new_node->tok_name = tok_name;
	new_node->next = NULL;
	return (new_node);
}

void	add_back_tok_lst(t_tok_lst **head, t_tok_lst *new_node)
{
	t_tok_lst	*temp;

	if (!head || !new_node)
		return ;
	if (!*head)
	{
		*head = new_node;
		return ;
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new_node;
}

void	free_tok_lst(t_tok_lst *head)
{
	t_tok_lst	*node;
	t_tok_lst	*next_node;

	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->content);
		free(node->tok_name);
		free(node);
		node = next_node;
	}
}


t_tok_lst	*last_token(t_tok_lst *head)
{
	t_tok_lst	*node;

	if (!head)
		return (NULL);
	node = head;
	while (node->next)
		node = node->next;
	return (node);
}

void	print_tok_lst(t_tok_lst *head)
{
	t_tok_lst	*node;
	int			i;

	node = (t_tok_lst *)head;
	i = 0;
	while (node)
	{
		ft_printf("token %d:\ncontent: %s\ntype: %d\ntok_name: %s\n\n",
			i, node->content, node->type, node->tok_name);
		node = node->next;
		i++;
	}
}
