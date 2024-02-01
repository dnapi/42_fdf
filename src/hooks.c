/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apimikov <apimikov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 10:06:54 by apimikov          #+#    #+#             */
/*   Updated: 2024/02/01 10:07:02 by apimikov         ###   ########.fr       */
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
	if (mlx_is_key_down(((t_fdf *)fdf)->mlx, MLX_KEY_UP))
		((t_fdf *)fdf)->cam.shifty -= 5;
	if (mlx_is_key_down(((t_fdf *)fdf)->mlx, MLX_KEY_DOWN))
		((t_fdf *)fdf)->cam.shifty += 5;
	if (mlx_is_key_down(((t_fdf *)fdf)->mlx, MLX_KEY_LEFT))
		((t_fdf *)fdf)->cam.shiftx -= 5;
	if (mlx_is_key_down(((t_fdf *)fdf)->mlx, MLX_KEY_RIGHT))
		((t_fdf *)fdf)->cam.shiftx += 5;
	if (mlx_is_key_down(((t_fdf *)fdf)->mlx, MLX_KEY_Z))
		((t_fdf *)fdf)->cam.zoom *= 1.1;
	if (mlx_is_key_down(((t_fdf *)fdf)->mlx, MLX_KEY_X) && \
		((t_fdf *)fdf)->cam.zoom > 0.01)
		((t_fdf *)fdf)->cam.zoom /= 1.1;
	if (mlx_is_key_down(((t_fdf *)fdf)->mlx, MLX_KEY_R))
		((t_fdf *)fdf)->cam.angx += 0.05;
	if (mlx_is_key_down(((t_fdf *)fdf)->mlx, MLX_KEY_E))
		((t_fdf *)fdf)->cam.angx -= 0.05;
	if (mlx_is_key_down(((t_fdf *)fdf)->mlx, MLX_KEY_F))
		((t_fdf *)fdf)->cam.angz += 0.05;
	if (mlx_is_key_down(((t_fdf *)fdf)->mlx, MLX_KEY_D))
		((t_fdf *)fdf)->cam.angz -= 0.05;
}

void	keyhook_event(mlx_key_data_t keydata, void *data)
{
	t_fdf	*fdf;

	fdf = data;
	if (keydata.key == MLX_KEY_C && keydata.action == MLX_PRESS)
		fdf->cam.color = (fdf->cam.color + 1) % 4;
	if (keydata.key == MLX_KEY_P && keydata.action == MLX_PRESS)
	{
		fdf->cam.angz = 0;
		fdf->cam.angx = PI / 2;
	}
}

// Print the window width and height.
void	ft_hook_print(void *data)
{
	t_fdf	*fdf;

	fdf = data;
	ft_printf("z->%d | x->%d | c->%d\n", (int)(360 * fdf->cam.angz / PI), \
		(int)(360 * fdf->cam.angx / 2 / PI), fdf->cam.color);
}
