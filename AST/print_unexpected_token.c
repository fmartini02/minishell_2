/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unexpected_token.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalloli <mdalloli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:12:45 by mdalloli          #+#    #+#             */
/*   Updated: 2025/06/30 18:13:11 by mdalloli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_unexpected_token(t_tok_lst **tokens)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	if (!is_valid_token(tokens))
		ft_putstr_fd("newline", 2);
	else
		ft_putstr_fd((char *)(*tokens)->content, 2);
	ft_putendl_fd("`", 2);
}
