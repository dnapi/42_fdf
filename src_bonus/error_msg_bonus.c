/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apimikov <apimikov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 11:04:30 by apimikov          #+#    #+#             */
/*   Updated: 2024/02/02 12:09:39 by apimikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf_bonus.h"

// error msgs
void	*null_err(char *msg)
{
	ft_putstr_fd(msg, 2);
	return (NULL);
}

int	value_err(char *msg, int err)
{
	ft_putstr_fd(msg, 2);
	return (err);
}

int	value_err_free(char *msg, int err, t_fdf *fdf)
{
	free_fdf(fdf);
	ft_putstr_fd(msg, 2);
	return (err);
}

int	perror_value_free(char *msg, int err, t_fdf *fdf)
{
	free_fdf(fdf);
	perror(msg);
	return (err);
}
