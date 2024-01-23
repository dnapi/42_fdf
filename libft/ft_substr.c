/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apimikov <apimikov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 09:33:34 by apimikov          #+#    #+#             */
/*   Updated: 2023/11/06 16:07:30 by apimikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	min(size_t x, size_t y);

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	len_s;
	size_t	len_sub;
	size_t	i;
	char	*pnt;

	if (!s)
		return (NULL);
	i = 0;
	len_s = ft_strlen(s);
	len_sub = 0;
	if (len_s > start)
		len_sub = min(len, len_s - start);
	pnt = malloc(len_sub + 1);
	if (!pnt)
		return (NULL);
	while (i < len_sub)
	{
		pnt[i] = s[start + i];
		i++;
	}
	pnt[i] = '\0';
	return (pnt);
}

size_t	min(size_t x, size_t y)
{
	if (x < y)
		return (x);
	return (y);
}
