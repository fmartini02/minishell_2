/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <fmartini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 22:39:01 by fmartini          #+#    #+#             */
/*   Updated: 2024/01/27 22:39:01 by fmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "std_fun.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*nxt;

	if (!lst || !(*lst))
		return ;
	while ((*lst)->next)
	{
		nxt = (*lst)->next;
		ft_lstdelone(*lst, (*del));
		*lst = nxt;
	}
	ft_lstdelone(*lst, (*del));
	*lst = NULL;
}
