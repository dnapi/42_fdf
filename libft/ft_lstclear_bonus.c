/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apimikov <apimikov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 07:06:46 by apimikov          #+#    #+#             */
/*   Updated: 2023/11/13 07:06:53 by apimikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*pnt;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		pnt = *lst;
		*lst = (*lst)->next;
		ft_lstdelone(pnt, del);
	}
}
