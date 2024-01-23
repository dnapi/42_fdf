/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apimikov <apimikov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:24:20 by apimikov          #+#    #+#             */
/*   Updated: 2023/11/06 16:05:09 by apimikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	in_set(char c, char const *set);

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	size_t	i1;
	size_t	i2;
	char	*pnt;

	if (!s1 || !set)
		return (NULL);
	i1 = 0;
	len = ft_strlen(s1);
	i2 = len - 1;
	while (s1[i1] && in_set(s1[i1], set))
		i1++;
	if (i1 == len)
		return (ft_strdup(""));
	while (in_set(s1[i2], set) && i2)
		i2--;
	pnt = ft_substr(s1, (unsigned int)i1, (size_t)(i2 - i1 + 1));
	return (pnt);
}

int	in_set(char c, char const *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}
