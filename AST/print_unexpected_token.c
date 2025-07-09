/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unexpected_token.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:10:08 by mdalloli          #+#    #+#             */
/*   Updated: 2025/07/08 19:13:29 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_unexpected_token(t_tok_lst **tokens)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	if (!is_valid_token(tokens))
		ft_putstr_fd("newline", 2);
	else
		ft_putstr_fd((*tokens)->content, 2);
	ft_putendl_fd("`", 2);
}
