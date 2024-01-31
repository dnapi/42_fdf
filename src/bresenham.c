/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apimikov <apimikov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:55:14 by apimikov          #+#    #+#             */
/*   Updated: 2024/01/31 17:23:54 by apimikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

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
	fdf->vec[k].x = fdf->cam.zoom * (fdf->vec[k].x + fdf->cam.shiftx) + size / 2;
	fdf->vec[k].y = fdf->cam.zoom * (fdf->vec[k].y + fdf->cam.shifty) + size / 2;
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

void	set_bresenham(t_vec r0, t_vec r1, t_brsnhm *brs)
{
	brs->d[0] = ft_abs_i(r1.x - r0.x);
	brs->d[1] = ft_abs_i(r1.y - r0.y);
	brs->s[0] = ft_sign(r1.x - r0.x);
	brs->s[1] = ft_sign(r1.y - r0.y);
	brs->e[0] = brs->d[0] - brs->d[1];
}



uint32_t	color_gradient(long z, t_vec r0, t_vec r1, t_fdf *fdf)
{
	int		c[3];
	float	dz;
	int 	rgb[2];

	dz = ft_max(1, fdf->max_z - fdf->min_z);
	if (fdf->cam.color == 2)
	{
		dz = ft_max(1, fdf->max_z - fdf->min_z);
		c[0] = (z - fdf->min_z) * (REDMAX - REDMIN)	/ dz + REDMIN;
		c[1] = (z - fdf->min_z) * (GREENMAX - GREENMIN) / dz + GREENMIN;
		c[2] = (z - fdf->min_z) * (BLUEMAX - BLUEMIN)	/ dz + BLUEMIN;
		return (c[0] << 24 | c[1] << 16 | c[2] << 8 | 150);
	}
	dz = ft_max(1, ft_abs_i(r1.z - r0.z));
	rgb[0] = (r0.c >> 24) & 0xFF;
	rgb[1] = (r1.c >> 24) & 0xFF;
//	c[0] = (z - fdf->min_z) * (rgb[1] - rgb[0])	/ dz + rgb[0];
	c[0] = ft_abs_i(z - r0.z) * (rgb[1] - rgb[0])	/ dz + rgb[0];
	rgb[0] = (r0.c >> 16) & 0xFF;
	rgb[1] = (r1.c >> 16) & 0xFF;
//	c[1] = (z - fdf->min_z) * (rgb[1] - rgb[0])	/ dz + rgb[0];
	c[1] = ft_abs_i(z - r0.z) * (rgb[1] - rgb[0])	/ dz + rgb[0];
	rgb[0] = (r0.c >> 8) & 0xFF;
	rgb[1] = (r1.c >> 8) & 0xFF;
//	c[2] = (z - fdf->min_z) * (rgb[1] - rgb[0])	/ dz + rgb[0];
	c[2] = ft_abs_i(z - r0.z) * (rgb[1] - rgb[0])	/ dz + rgb[0];
	return (c[0] << 24 | c[1] << 16 | c[2] << 8 | 255);
}

uint32_t	color_select(t_brsnhm *brs, t_vec r0, t_vec r1, t_fdf *fdf)
{
	long	z;

	if (fdf->cam.color == 0)
		return (DEFAULTCOLOR);
	if (fdf->cam.color == 1)
	{
		if (r0.z > r1.z)
			return (r0.c);
		else
			return (r1.c);
	}
	if (brs->d[0] > brs->d[1] && brs->d[0] > 0)
		z = (1 - (r1.x - r0.x) / brs->d[0]) * (r1.z - r0.z) + r0.z;
	else if (brs->d[1] > brs->d[0] && brs->d[1] > 0)
		z = (1 - (r1.y - r0.y) / brs->d[1]) * (r1.z - r0.z) + r0.z;
	else
		z = r0.z;
	return (color_gradient(z, r0, r1, fdf));
}

void	bresenham_mod(t_vec r0, t_vec r1, t_fdf *fdf)
{
	t_brsnhm	brs;
	uint32_t	color;

	set_bresenham(r0, r1, &brs);
	while (r0.x != r1.x || r0.y != r1.y)
	{
		color = color_select(&brs, r0, r1, fdf);
		if (is_pixel(r0, fdf))
			mlx_put_pixel(fdf->image, r0.x, r0.y, color);
		brs.e[1] = 2 * brs.e[0];
		if (brs.e[1] > -brs.d[1])
		{
			brs.e[0] -= brs.d[1];
			r0.x += brs.s[0];
		}
		if (brs.e[1] < brs.d[0])
		{
			brs.e[0] += brs.d[0];
			r0.y += brs.s[1];
		}
	}
	color = color_select(&brs, r0, r1, fdf);
	if (is_pixel(r0, fdf))
		mlx_put_pixel(fdf->image, r0.x, r0.y, color);
}