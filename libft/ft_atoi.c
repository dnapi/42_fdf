/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apimikov <apimikov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 13:13:34 by apimikov          #+#    #+#             */
/*   Updated: 2023/11/15 07:11:41 by apimikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int			sign;
	long long	answ;
	long long	llong_max;

	llong_max = ((unsigned long long)(-1)) / 2;
	sign = 1;
	answ = 0;
	while ((8 < *str && *str < 14) || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign = -1;
	while ('0' <= *str && *str <= '9')
	{
		if (answ > llong_max / 10)
			return ((sign > 0) * (-1));
		answ = answ * 10;
		if (answ > llong_max - (*str - '0'))
			return ((sign > 0) * (-1));
		answ = answ + ((*str++) - '0');
	}
	return ((int)(sign * answ));
}
