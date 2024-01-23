/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apimikov <apimikov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 11:32:30 by apimikov          #+#    #+#             */
/*   Updated: 2023/11/13 15:15:50 by apimikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*pnt;

	pnt = malloc(sizeof(t_list));
	if (!pnt)
		return (NULL);
	pnt->content = content;
	pnt->next = NULL;
	return (pnt);
}
