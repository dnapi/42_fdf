/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apimikov <apimikov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:55:14 by apimikov          #+#    #+#             */
/*   Updated: 2024/02/01 15:44:16 by apimikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	set_bresenham(t_vec r0, t_vec r1, t_brsnhm *brs)
{
	brs->d[0] = ft_abs_i(r1.x - r0.x);
	brs->d[1] = ft_abs_i(r1.y - r0.y);
	brs->s[0] = ft_sign(r1.x - r0.x);
	brs->s[1] = ft_sign(r1.y - r0.y);
	brs->e[0] = brs->d[0] - brs->d[1];
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
