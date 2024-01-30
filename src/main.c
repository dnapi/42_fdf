#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "../include/MLX42.h"
#include "../include/fdf.h"

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);

}

/*
int ft_abs_i(int i)
{
	return (i * (i >= 0) - i * (i < 0));
}

int	ft_sign(int i)
{
	return ((i >= 0) - (i < 0));
}

int	ft_max(int a, int b)
{
	return (a * (a >= b) + b * (a < b));
}

int	ft_min(int a, int b)
{
	return (a * (a <= b) + b * (a > b));
}
*/

/*
void	move_vec(int k, t_fdf *fdf, int j, int i)
{
	float	n;
	float	r[3];
	float	size;

	n = fdf->size_x;
	size = (float)(fdf->image->width);
	r[2] = (fdf->z[j][i] - fdf->min_z) * size / ft_max(fdf->max_z - fdf->min_z, 1) / 10;
	r[1] = (j - (n - 1) / 2) * size / (n + 1) / 2;
	r[0] = (i - (n - 1) / 2) * size / (n + 1) / 2;
	fdf->vec[k].x = cosf(fdf->cam.angz) * r[0] - sinf(fdf->cam.angz) * r[1];
	fdf->vec[k].y = cosf(fdf->cam.angx) * (cosf(fdf->cam.angz) * r[1] \
					+ sinf(fdf->cam.angz) * r[0]) - sinf(fdf->cam.angx) * r[2];
	fdf->vec[k].x = fdf->cam.zoom * (fdf->vec[k].x + fdf->cam.shiftx) + size / 2;
	fdf->vec[k].y = fdf->cam.zoom * (fdf->vec[k].y + fdf->cam.shifty) + size / 2;
	fdf->vec[k].z = fdf->z[j][i];
	fdf->vec[k].c = 0xFFFFFFFF;
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

void	bresenham_mod(t_vec r0, t_vec r1, t_fdf *fdf)
{
	t_brsnhm	brs;
	uint32_t	color;

	set_bresenham(r0, r1, &brs);
	color = 0xFFFFFFFF;
	while (r0.x != r1.x || r0.y != r1.y)
	{
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
	if (is_pixel(r0, fdf))
		mlx_put_pixel(fdf->image, r0.x, r0.y, color);
}
*/


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

void	ft_line(void *data)
{
	t_fdf	*fdf;
	int		i;
	int		j;

	fdf = data;
	ft_memset(fdf->image->pixels, CHANNELBACK,
		fdf->image->width * fdf->image->height * sizeof(int32_t));
	i = -1;
	j = -1;
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
static void	ft_mlx_error(t_fdf *fdf)
{
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
		ft_mlx_error(fdf);
	fdf->image = mlx_new_image(fdf->mlx, IMAGEWIDTH, IMAGEHEIGHT);
	if (!fdf->image)
	{
		mlx_close_window(fdf->mlx);
		ft_mlx_error(fdf);
	}
	if (mlx_image_to_window(fdf->mlx, fdf->image, 0, 0) == -1)
	{
		mlx_close_window(fdf->mlx);
		ft_mlx_error(fdf);
	}
	mlx_loop_hook(fdf->mlx, ft_hook_print, fdf);
	mlx_loop_hook(fdf->mlx, ft_line, fdf);
	mlx_loop_hook(fdf->mlx, ft_hook, fdf);
	mlx_loop(fdf->mlx);
	mlx_terminate(fdf->mlx);
	free_fdf(fdf);
	return (EXIT_SUCCESS);
}
