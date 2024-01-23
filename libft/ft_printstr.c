/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apimikov <apimikov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 06:44:41 by apimikov          #+#    #+#             */
/*   Updated: 2024/01/08 10:31:38 by apimikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

int	ft_printstr(char *s)
{
	int	len;

	if (!s)
		return (write(1, "(null)", 6));
	len = ft_strlen(s);
	return (write(1, s, len));
}
