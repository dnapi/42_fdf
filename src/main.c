#include "../include/MLX42.h"
#include "../include/fdf.h"

/*
int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);

}
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

/*
void	ft_hook_key(void *data)
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
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_E))
		fdf->cam.angx -= 0.05;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_F))
		fdf->cam.angz += 0.05;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_D))
		fdf->cam.angz -= 0.05;
}
*/

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
}

// Print the window width and height.
static void	ft_hook_print(void *data)
{
	t_fdf	*fdf;

	fdf = data;
	ft_printf("z->%d | x->%d | c->%d\n", (int)(360 * fdf->cam.angz / PI), \
		(int)(360 * fdf->cam.angx / 2 / PI), fdf->cam.color);
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
	mlx_loop_hook(fdf->mlx, ft_hook_image, fdf);
	mlx_loop_hook(fdf->mlx, ft_hook_key, fdf);
	mlx_key_hook(fdf->mlx, &keyhook_event, fdf);
	mlx_loop(fdf->mlx);
	mlx_terminate(fdf->mlx);
	free_fdf(fdf);
	return (EXIT_SUCCESS);
}
