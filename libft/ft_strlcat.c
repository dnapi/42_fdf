/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apimikov <apimikov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 08:48:51 by apimikov          #+#    #+#             */
/*   Updated: 2023/11/14 15:46:40 by apimikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len_d;
	size_t	len_s;

	len_s = 0;
	len_d = 0;
	while (*src && src[len_s])
		len_s++;
	if (!dst && !dstsize)
		return (len_s);
	while (dst[len_d] && len_d <= dstsize)
		len_d++;
	if (dstsize == 0 || dstsize <= len_d)
		return (len_s + dstsize);
	while (*dst)
	{
		dst++;
		dstsize--;
	}
	while (--dstsize > 0 && *src)
		*dst++ = *src++;
	*dst = '\0';
	return (len_s + len_d);
}
