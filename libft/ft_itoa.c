/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apimikov <apimikov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:29:16 by apimikov          #+#    #+#             */
/*   Updated: 2023/11/06 16:02:00 by apimikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

long	len_num(long num);
long	ft_abs(long num);

char	*ft_itoa(int n)
{
	char	*pnt;
	long	len;
	long	num;
	int		sign;

	sign = 0;
	num = ft_abs((long)n);
	if (n < 0)
		sign = 1;
	len = len_num(num) + sign;
	pnt = malloc((len + 1) * sizeof(char));
	if (!pnt)
		return (NULL);
	pnt[len] = '\0';
	while (len-- > sign)
	{
		pnt[len] = num % 10 + '0';
		num = num / 10;
	}
	if (sign)
		*pnt = '-';
	return (pnt);
}

long	len_num(long num)
{
	long	order;

	num = ft_abs(num);
	order = 1;
	while (num > 9)
	{
		num = num / 10;
		order++;
	}
	return (order);
}

long	ft_abs(long num)
{
	if (num < 0)
		return (-num);
	return (num);
}
