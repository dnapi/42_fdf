/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fdf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apimikov <apimikov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 11:03:59 by apimikov          #+#    #+#             */
/*   Updated: 2024/02/01 11:04:01 by apimikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// initialization of fdf structure
t_fdf	*init_fdf(int argc, char *argv[])
{
	t_fdf	*fdf;
	char	*pnt;

	if (argc != 2)
		return (null_err("Error: wrong number of arguments.\n"));
	fdf = (t_fdf *)malloc(sizeof(t_fdf) * 1);
	if (!fdf)
		return (null_err("Error: fdf malloc problem\n"));
	fdf->argv = argv;
	set_size_xy(fdf);
	fdf->fd = open(argv[1], O_RDONLY);
	if (fdf->fd == -1)
		return (null_err("Error: can't open file\n"));
	set_z_matrix(fdf);
	set_z_minmax(fdf);
	set_camera(fdf);
	return (fdf);
}

void	ft_free_char2d(char **split)
{
	size_t	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		split[i] = NULL;
		i++;
	}
	free(split);
	split = NULL;
}

void	free_int_2d(long **m, size_t sizey)
{
	size_t	i;

	if (!m)
		return ;
	i = 0;
	while (i < sizey)
	{
		if (m[i])
		{
			free(m[i]);
			m[i] = NULL;
		}
		i++;
	}
	free(m);
	m = NULL;
}

void	free_fdf(t_fdf *fdf)
{
	if (!fdf)
		return ;
	if (!fdf->z)
		free_int_2d(fdf->z, fdf->size_y);
	if (!fdf->c)
		free_int_2d(fdf->c, fdf->size_y);
	free(fdf);
	fdf = NULL;
}
