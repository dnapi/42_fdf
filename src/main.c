//#include <stdint.h>
//#include <stdbool.h>
#include "../include/MLX42.h"
#include "../include/fdf.h"

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);

}

/*
void	fill_image(t_fdf *fdf) 
{
	int	i;
	int	j;
	
	i = -1;
	while (++i < fdf->image->width)
	{
		j = -1;
		while (++j < fdf->image->height) 
			mlx_put_pixel(fdf->image, i, j, IMAGEBACKGROUND);
	}
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

void	ft_fdf(void *data)
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

void	ft_hook(void *data)
{
	t_fdf	*fdf;

	fdf = data;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(fdf->mlx);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_UP))
		fdf->cam.shifty -= 5;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_DOWN))
		fdf->cam.shifty += 5;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_LEFT))
		fdf->cam.shiftx -= 5;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_RIGHT))
		fdf->cam.shiftx += 5;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_Z))
		fdf->cam.zoom *= 1.1;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_X) && fdf->cam.zoom > 0.01)
		fdf->cam.zoom /= 1.1;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_R))
		fdf->cam.angx += 0.05;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_F))
		fdf->cam.angz += 0.05;
}

// Print the window width and height.
static void	ft_hook_print(void *data)
{
	t_fdf	*fdf;

	fdf = data;
	printf("angz %f | angx: %f\n", fdf->cam.angz, fdf->cam.angx);
}

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
	mlx_loop_hook(fdf->mlx, ft_hook_print, fdf);
	mlx_loop_hook(fdf->mlx, ft_fdf, fdf);
	mlx_loop_hook(fdf->mlx, ft_hook, fdf);
	mlx_loop(fdf->mlx);
	mlx_terminate(fdf->mlx);
	free_fdf(fdf);
	return (EXIT_SUCCESS);
}
