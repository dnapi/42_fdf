/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apimikov <apimikov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 06:50:31 by apimikov          #+#    #+#             */
/*   Updated: 2023/11/07 09:04:10 by apimikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	len_n;

	if (!haystack && !len)
		return (NULL);
	i = 0;
	len_n = ft_strlen(needle);
	if (!len_n)
		return ((char *)haystack);
	while (*haystack && i + len_n <= len)
	{
		if (*haystack == *needle && ft_strncmp(haystack, needle, len_n) == 0)
			return ((char *)haystack);
		haystack++;
		i++;
	}
	return (NULL);
}
