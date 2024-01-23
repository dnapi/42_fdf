/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apimikov <apimikov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 08:02:25 by apimikov          #+#    #+#             */
/*   Updated: 2023/11/13 15:16:20 by apimikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*list;
	t_list	*node;
	void	*temp;

	if (!lst || !f || !del)
		return (NULL);
	list = NULL;
	while (lst)
	{
		temp = f(lst->content);
		node = ft_lstnew(temp);
		if (!node)
		{
			ft_lstclear(&list, del);
			del(temp);
			return (NULL);
		}
		ft_lstadd_back(&list, node);
		lst = lst->next;
	}
	return (list);
}
