/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_utils_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apimikov <apimikov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:55:14 by apimikov          #+#    #+#             */
/*   Updated: 2024/02/02 12:05:52 by apimikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf_bonus.h"

void	move_vec(int k, t_fdf *fdf, int j, int i)
{
	float	n;
	float	r[3];
	float	size;

	n = fdf->size_x;
	size = (float)(fdf->image->width);
	r[2] = (fdf->z[j][i] - fdf->min_z) * size / \
		ft_max(fdf->max_z - fdf->min_z, 1) / 10;
	r[1] = (j - (n - 1) / 2) * size / (n + 1) / 2;
	r[0] = (i - (n - 1) / 2) * size / (n + 1) / 2;
	fdf->vec[k].x = cosf(fdf->cam.angz) * r[0] - sinf(fdf->cam.angz) * r[1];
	fdf->vec[k].y = cosf(fdf->cam.angx) * (cosf(fdf->cam.angz) * r[1] \
					+ sinf(fdf->cam.angz) * r[0]) - sinf(fdf->cam.angx) * r[2];
	fdf->vec[k].x = fdf->cam.zoom * (fdf->vec[k].x + fdf->cam.shiftx) \
		+ size / 2;
	fdf->vec[k].y = fdf->cam.zoom * (fdf->vec[k].y + fdf->cam.shifty) \
		+ size / 2;
	fdf->vec[k].z = fdf->z[j][i];
	fdf->vec[k].c = fdf->c[j][i];
}

int	is_pixel(t_vec r0, t_fdf *fdf)
{
	if (r0.x >= 0 && r0.y >= 0 && \
			r0.x < fdf->image->width - 1 && r0.y < fdf->image->height - 1)
	{
		return (1);
	}
	return (0);
}

uint32_t	color_gradient(double z, t_vec r0, t_vec r1, t_fdf *fdf)
{
	int		c[3];
	float	dz;
	int		rgb[2];

	if (fdf->cam.color == 2)
	{
		dz = ft_max(1, fdf->max_z - fdf->min_z);
		c[0] = (int)(float)((z - fdf->min_z) * (REDMAX - REDMIN) / dz) + REDMIN;
		c[1] = (int)(float)((z - fdf->min_z) * (GREENMAX - GREENMIN) / dz) + GREENMIN;
		c[2] = (int)(float)((z - fdf->min_z) * (BLUEMAX - BLUEMIN) / dz) + BLUEMIN;
		return (c[0] << 24 | c[1] << 16 | c[2] << 8 | 150);
	}
	dz = ft_max(1, ft_abs_i(r1.z - r0.z));
	rgb[0] = (r0.c >> 24) & 0xFF;
	rgb[1] = (r1.c >> 24) & 0xFF;
	c[0] = ft_abs_i(z - r0.z) * (rgb[1] - rgb[0]) / dz + rgb[0];
	rgb[0] = (r0.c >> 16) & 0xFF;
	rgb[1] = (r1.c >> 16) & 0xFF;
	c[1] = ft_abs_i(z - r0.z) * (rgb[1] - rgb[0]) / dz + rgb[0];
	rgb[0] = (r0.c >> 8) & 0xFF;
	rgb[1] = (r1.c >> 8) & 0xFF;
	c[2] = ft_abs_i(z - r0.z) * (rgb[1] - rgb[0]) / dz + rgb[0];
	return (c[0] << 24 | c[1] << 16 | c[2] << 8 | 255);
}


/*
// new vession
uint32_t	color_gradient(float t, t_vec r0, t_vec r1, t_fdf *fdf)
{
	int		c[3];
	float	dz;
	int		rgb[2];

//	dz = ft_max(1, fdf->max_z - fdf->min_z);
	if (fdf->cam.color == 2)
	{
		//dz = ft_max(1, fdf->max_z - fdf->min_z);
	//	ft_printf("100 * t=%d\n", (int)(100 * t));
		c[0] = t * (REDMAX - REDMIN) + REDMIN;
		c[1] = t * (GREENMAX - GREENMIN) + GREENMIN;
		c[2] = t * (BLUEMAX - BLUEMIN) + BLUEMIN;
		return (c[0] << 24 | c[1] << 16 | c[2] << 8 | 150);
	}
	dz = ft_max(1, ft_abs_i(r1.z - r0.z));
	rgb[0] = (r0.c >> 24) & 0xFF;
	rgb[1] = (r1.c >> 24) & 0xFF;
	c[0] = t * (rgb[1] - rgb[0]) + rgb[0];
	rgb[0] = (r0.c >> 16) & 0xFF;
	rgb[1] = (r1.c >> 16) & 0xFF;
	c[1] = t * (rgb[1] - rgb[0]) + rgb[0];
	rgb[0] = (r0.c >> 8) & 0xFF;
	rgb[1] = (r1.c >> 8) & 0xFF;
	c[2] = t * (rgb[1] - rgb[0]) + rgb[0];
	return (c[0] << 24 | c[1] << 16 | c[2] << 8 | 255);
}
*/


uint32_t	color_select(t_brsnhm *brs, t_vec r0, t_vec r1, t_fdf *fdf)
{
	double	z;

	if (fdf->cam.color == 0)
		return (DEFAULTCOLOR);
	if (fdf->cam.color == 1)
	{
		if (r0.z < r1.z)
			return (r0.c);
		else
			return (r1.c);
	}
	if (brs->d[0] >= brs->d[1] && brs->d[0] > 0)
		z = (brs->d[0] - (r1.x - r0.x)) * (r1.z - r0.z) / brs->d[0] + r0.z;
	else if (brs->d[1] > brs->d[0] && brs->d[1] > 0)
		z = (brs->d[1] - (r1.y - r0.y)) * (r1.z - r0.z) / brs->d[1] + r0.z;
//		z = (1 - (r1.y - r0.y) / brs->d[1]) * (r1.z - r0.z) + r0.z;
	else
		z = r0.z;
	return (color_gradient(z, r0, r1, fdf));
}

/*
//new version
uint32_t	color_select(t_brsnhm *brs, t_vec r0, t_vec r1, t_fdf *fdf)
{
	float	t;

	if (fdf->cam.color == 0)
		return (DEFAULTCOLOR);
	if (fdf->cam.color == 1)
	{
		if (r0.z < r1.z)
			return (r0.c);
		else
			return (r1.c);
	}
	if (brs->d[0] >= brs->d[1] && brs->d[0] > 0)
		t = 1 - (float)ft_abs_i(r1.x - r0.x) / brs->d[0];
	else if (brs->d[1] > brs->d[0] && brs->d[1] > 0)
		t = 1 - (float)ft_abs_i(r1.y - r0.y) / brs->d[1];
	else
		t = 1;
	return (color_gradient(t, r0, r1, fdf));
}
	*/

void	ft_plot_lines(t_fdf *fdf, int i, int j)
{
	while (++j < fdf->size_y - 1)
	{
		i = -1;
		while (++i < fdf->size_x - 1)
		{
			move_vec(0, fdf, j, i);
			move_vec(1, fdf, j + 1, i);
			bresenham_mod(fdf->vec[0], fdf->vec[1], fdf);
			move_vec(1, fdf, j, i + 1);
			bresenham_mod(fdf->vec[0], fdf->vec[1], fdf);
		}
		move_vec(0, fdf, j, i);
		move_vec(1, fdf, j + 1, i);
		bresenham_mod(fdf->vec[0], fdf->vec[1], fdf);
	}
	i = -1;
	while (++i < fdf->size_x - 1)
	{
		move_vec(0, fdf, j, i);
		move_vec(1, fdf, j, i + 1);
		bresenham_mod(fdf->vec[0], fdf->vec[1], fdf);
	}
}