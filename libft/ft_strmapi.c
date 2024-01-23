/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apimikov <apimikov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 06:54:37 by apimikov          #+#    #+#             */
/*   Updated: 2023/11/07 06:56:24 by apimikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*pnt;
	size_t			len;
	unsigned int	i;

	if (!s)
		return (NULL);
	i = 0;
	len = ft_strlen(s);
	pnt = malloc(len + 1);
	if (!pnt)
		return (NULL);
	while (i < len)
	{
		pnt[i] = f(i, s[i]);
		i++;
	}
	pnt[i] = '\0';
	return (pnt);
}
