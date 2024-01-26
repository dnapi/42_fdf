// -----------------------------------------------------------------------------
// Codam Coding College, Amsterdam @ 2022-2023 by W2Wizard.
// See README in the root project for more information.
// -----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "../include/MLX42.h"
#include "fdf.h"

//static mlx_image_t* image;

// -----------------------------------------------------------------------------

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

int	ft_abs(int i)
{
	return( i * (i >= 0) - i * (i < 0));
}

int	ft_sign(int i)
{
	return( (i >= 0) -  (i < 0));
}

/*
void bresenham_mod(t_vec_2d r0, t_vec_2d r1, t_fdf *fdf) 
{
	int	d[2];
	int	s[2];
    int err;
	int	err2;
	int	i;

    d[0] = ft_abs(r1.x - r0.x);
    d[1] = ft_abs(r1.y - r0.y);
    err = d[0] - d[1];
    s[0] = ft_sign(r1.x - r0.x);
    s[1] = ft_sign(r1.y - r0.y);
	i = 0;
 	color = 0xFFFFFFFF;	
    while ((x0 != x1 || y0 != y1) && \
			x0 < fdf->image->width && y0 < fdf->image->height ) 
	{
		mlx_put_pixel(fdf->image, x0, y0, color);
        err2 = 2 * err;
        if (err2 > -d[1]) 
		{
            err -= d[1];
            x0 += s[0];
        }
        if (err2 < d[0]) 
		{
            err += d[0];
            y0 += s[1];
        }
    }
	mlx_put_pixel(fdf->image, x1, y1, color);
}
*/

void bresenham(int x0, int y0, int x1, int y1, t_fdf *fdf) 
{
	int	d[2];
	int	s[2];
    int err;
	int	err2;
	uint32_t color;
	int	i;

    d[0] = ft_abs(x1 - x0);
    d[1] = ft_abs(y1 - y0);
    err = d[0] - d[1];
    s[0] = ft_sign(x1 - x0);
    s[1] = ft_sign(y1 - y0);
	i = 0;
 	color = 0xFFFFFFFF;	
    while ((x0 != x1 || y0 != y1) && \
			x0 < fdf->image->width - 1 && y0 < fdf->image->height - 1) 
	{
		mlx_put_pixel(fdf->image, x0, y0, color);
        err2 = 2 * err;
        if (err2 > -d[1]) 
		{
            err -= d[1];
            x0 += s[0];
        }
        if (err2 < d[0]) 
		{
            err += d[0];
            y0 += s[1];
        }
    }
	mlx_put_pixel(fdf->image, x0, y0, color);
}

void fill_image(t_fdf *fdf) 
{
	int	i;
	int	j;
	
	i = -1;
    while (++i < fdf->image->width)
	{
		j = -1;
		while (++j < fdf->image->height) 
		{
			mlx_put_pixel(fdf->image, i, j, IMAGEBACKGROUND);
    	}
	}
}

void ft_line(void *data)
{
	t_fdf	*fdf;

	fdf = data;

	fill_image(data); 
	bresenham(0, 0,  100, fdf->temp, fdf);
}

void ft_hook(void *data)
{
	t_fdf	*fdf;

	fdf = data;
	mlx_t* mlx = fdf->mlx;
	mlx_image_t *image = fdf->image;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		image->instances[0].y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		image->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		image->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		image->instances[0].x += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_T))
		fdf->temp += 10;
	if (mlx_is_key_down(mlx, MLX_KEY_Y) && fdf->temp > 10)
	{
		fdf->temp -= 10;
//		fill_image(data); 
	}
}

// Print the window width and height.
static void ft_hook_print(void* data)
{
	t_fdf	*fdf;

	fdf = data;

//	sleep(1);
	printf("WIDTH: %d | HEIGHT: %d\n", fdf->mlx->width, fdf->mlx->height);
	printf("WIDTH: %d | HEIGHT: %d\n", fdf->image->width, fdf->image->height);
}

// Exit the program as failure.
static void ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

// -----------------------------------------------------------------------------

int32_t main(int32_t argc, const char* argv[])
{
	t_fdf	fdf;

	(void)argc;
	(void)argv;

	// Gotta error check this stuff
	if (!(fdf.mlx = mlx_init(MLXWIDTH, MLXHEIGHT, "MLX42", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (!(fdf.image = mlx_new_image(fdf.mlx, IMAGEWIDTH, IMAGEHEIGHT)))
	{
		mlx_close_window(fdf.mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(fdf.mlx, fdf.image, 0, 0) == -1)
	{
		mlx_close_window(fdf.mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}

	mlx_image_t* img = mlx_new_image(fdf.mlx, IMAGEWIDTH, IMAGEHEIGHT);
	if (!img || (mlx_image_to_window(fdf.mlx, img, 0, 0) < 0))
		ft_error();	

	mlx_put_pixel(img, 0, 0, 0xFF0000FF);
	mlx_put_pixel(img, 10, 10, 0xFF0000FF);
	mlx_loop_hook(fdf.mlx, ft_hook_print, &fdf);
//	mlx_loop_hook(mlx, ft_randomize, mlx);
	mlx_loop_hook(fdf.mlx, ft_line, &fdf);
	mlx_loop_hook(fdf.mlx, ft_hook, &fdf);

	mlx_loop(fdf.mlx);
	mlx_terminate(fdf.mlx);
	return (EXIT_SUCCESS);
}

