/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apimikov <apimikov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 08:34:30 by apimikov          #+#    #+#             */
/*   Updated: 2023/11/23 09:59:25 by apimikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_positive(int nb, int fd);

void	ft_putnbr_fd(int nb, int fd)
{
	if (nb == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	else if (nb < 0)
	{
		write(fd, "-", 1);
		nb = -nb;
	}
	ft_putnbr_positive(nb, fd);
}

void	ft_putnbr_positive(int nb, int fd)
{
	if (nb > 9)
	{
		ft_putnbr_positive(nb / 10, fd);
		nb = nb % 10 + '0';
		write(fd, &nb, 1);
	}
	else
	{
		nb = nb + '0';
		write(fd, &nb, 1);
	}
}
