/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apimikov <apimikov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 10:07:51 by apimikov          #+#    #+#             */
/*   Updated: 2024/02/02 11:21:09 by apimikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MLX42.h"
#include "../include/fdf.h"

// Exit the program as failure.
static void	ft_mlx_error(t_fdf *fdf, int close_win)
{
	if (close_win)
		mlx_close_window(fdf->mlx);
	free_fdf(fdf);
	ft_putstr_fd((char *)mlx_strerror(mlx_errno), 2);
	exit(EXIT_FAILURE);
}

int32_t	main(int32_t argc, char *argv[])
{
	t_fdf	*fdf;

	fdf = init_fdf(argc, argv);
	if (!fdf)
		return (1);
	fdf->mlx = mlx_init(MLXWIDTH, MLXHEIGHT, "MLX42", true);
	if (!fdf->mlx)
		ft_mlx_error(fdf, 0);
	fdf->image = mlx_new_image(fdf->mlx, IMAGEWIDTH, IMAGEHEIGHT);
	if (!fdf->image)
		ft_mlx_error(fdf, 1);
	if (mlx_image_to_window(fdf->mlx, fdf->image, 0, 0) == -1)
		ft_mlx_error(fdf, 1);
	mlx_loop_hook(fdf->mlx, ft_hook_image, fdf);
	mlx_loop_hook(fdf->mlx, ft_hook_key, fdf);
	mlx_loop(fdf->mlx);
	mlx_terminate(fdf->mlx);
	free_fdf(fdf);
	return (EXIT_SUCCESS);
}
