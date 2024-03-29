/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apimikov <apimikov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 10:06:54 by apimikov          #+#    #+#             */
/*   Updated: 2024/02/01 16:50:37 by apimikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MLX42.h"
#include "../include/fdf.h"

void	ft_hook_image(void *data)
{
	t_fdf	*fdf;
	int		i;
	int		j;

	fdf = data;
	ft_memset(fdf->image->pixels, CHANNELBACK,
		fdf->image->width * fdf->image->height * sizeof(int32_t));
	i = -1;
	j = -1;
	ft_plot_lines(fdf, i, j);
}

void	ft_hook_key(void *fdf)
{
	if (mlx_is_key_down(((t_fdf *)fdf)->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(((t_fdf *)fdf)->mlx);
}
