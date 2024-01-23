/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apimikov <apimikov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 08:46:25 by apimikov          #+#    #+#             */
/*   Updated: 2023/11/13 12:10:19 by apimikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	num;
	size_t	max;

	max = (size_t)-1;
	if (count > 0 && max / count < size)
		return (NULL);
	num = count * size;
	ptr = (void *)malloc(num);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, num);
	return (ptr);
}
