/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apimikov <apimikov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 16:04:25 by apimikov          #+#    #+#             */
/*   Updated: 2023/10/30 16:04:28 by apimikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *b, size_t len)
{
	unsigned char	*pnt;

	pnt = b;
	while (len--)
	{
		*pnt = 0;
		pnt++;
	}
}
