/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fdf_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apimikov <apimikov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 11:05:03 by apimikov          #+#    #+#             */
/*   Updated: 2024/02/01 16:27:58 by apimikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf_bonus.h"

// init z matrix
long	**alloc_2d_long(size_t size_x, size_t size_y)
{
	long	**z;
	size_t	i;
	size_t	x;

	z = (long **)malloc(sizeof(long *) * size_y);
	if (!z)
		return (null_err("Error: memory problem \n"));
	i = -1;
	while (++i < size_y)
	{
		z[i] = (long *)malloc(sizeof(long) * size_x);
		if (!z[i])
		{
			while (--i >= 0)
				free(z[i]);
			free(z);
			return (null_err("Error: memory problem \n"));
		}
		x = -1;
		while (++x < size_x)
			z[i][x] = 0;
	}
	return (z);
}

void	init_zc_matrices(t_fdf *fdf)
{
	long	*c;

	fdf->z = alloc_2d_long(fdf->size_x, fdf->size_y);
	if (!fdf->z)
		exit(value_err_free("Error: malloc alloc_2d_long\n", 1, fdf));
	fdf->c = alloc_2d_long(fdf->size_x, fdf->size_y);
	if (!fdf->c)
		exit(value_err_free("Error: malloc alloc_2d_long\n", 1, fdf));
}

void	set_z_matrix(t_fdf *fdf)
{
	char	*str;
	char	**row;
	size_t	y;

	init_zc_matrices(fdf);
	y = -1;
	while (++y < fdf->size_y)
	{
		str = get_next_line(fdf->fd);
		if (!str)
			break ;
		row = ft_split(str, ' ');
		free(str);
		if (!row)
			exit(value_err_free("Error: close file error\n", 1, fdf));
		str_to_long(row, fdf->z[y], fdf->size_x, fdf);
		str_to_color(row, fdf->c[y], fdf->size_x, fdf);
		ft_free_char2d(row);
	}
	if (close(fdf->fd) == -1)
		exit(value_err_free("Error: close file error\n", 1, fdf));
	return ;
}

void	set_z_minmax(t_fdf *fdf)
{
	size_t	i;
	size_t	j;
	long	z[2];

	z[0] = 0;
	z[1] = 0;
	j = -1;
	while (++j < fdf->size_y)
	{
		i = -1;
		while (++i < fdf->size_x)
		{
			z[0] = ft_min(z[0], fdf->z[j][i]);
			z[1] = ft_max(z[1], fdf->z[j][i]);
		}
	}
	fdf->min_z = z[0];
	fdf->max_z = z[1];
}

void	set_camera(t_fdf *fdf)
{
	fdf->cam.iso = 1;
	fdf->cam.angz = 3.1415 / 4;
	fdf->cam.angx = 0.95531;
	fdf->cam.shiftx = 0;
	fdf->cam.shifty = 0;
	fdf->cam.zoom = 1;
	fdf->cam.color = 0;
}
