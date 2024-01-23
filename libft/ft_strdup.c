/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apimikov <apimikov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 09:27:25 by apimikov          #+#    #+#             */
/*   Updated: 2024/01/15 11:52:05 by apimikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	int		len;
	char	*pnt;

	i = 0;
	len = ft_strlen(s1);
	pnt = malloc(len + 1);
	if (!pnt)
		return (NULL);
	while (i < len)
	{
		pnt[i] = s1[i];
		i++;
	}
	pnt[i] = '\0';
	return (pnt);
}
