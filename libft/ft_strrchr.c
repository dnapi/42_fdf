/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apimikov <apimikov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 09:07:16 by apimikov          #+#    #+#             */
/*   Updated: 2023/11/01 09:07:18 by apimikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (*s)
	{
		i++;
		s++;
	}
	if ((char)c == *s)
		return ((char *)s);
	else
		s--;
	while (i)
	{
		if (*s == (char)c)
			return ((char *)s);
		i--;
		s--;
	}
	return (NULL);
}
