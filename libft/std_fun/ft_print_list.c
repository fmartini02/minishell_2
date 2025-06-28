/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdalloli <mdalloli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:02:13 by francema          #+#    #+#             */
/*   Updated: 2025/06/28 17:02:39 by mdalloli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_print_list(t_list *lst, char cast)
{
	t_list	*tmp;

	if (!lst)
		return ;
	tmp = lst;
	while (tmp)
	{
		if (cast == 's')
			ft_printf("%s\n", (char *)tmp->content);
		else if (cast == 'p')
			ft_printf("%p\n", (void *)tmp->content);
		tmp = tmp->next;
	}
}
