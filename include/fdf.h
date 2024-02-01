/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apimikov <apimikov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 07:20:43 by apimikov          #+#    #+#             */
/*   Updated: 2024/01/31 17:04:22 by apimikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

//#include <cstdint>
# define IMAGEWIDTH 1100
# define IMAGEHEIGHT 1100
# define MLXWIDTH 1100
# define MLXHEIGHT 1100
# define IMAGEBACKGROUND 0xff0000ff 
# define CHANNELBACK 100
# define DEFAULTCOLOR 0xffffffff
# define REDMIN 0
# define GREENMIN 0
# define BLUEMIN 254
# define REDMAX 255
# define GREENMAX 255
# define BLUEMAX 255
# define PI 3.14

//# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
//# include <stdlib.h>
//# include <string.h>
# include <math.h>
# include "libft.h"
# include "MLX42.h"

typedef	struct s_vec
{
	int				x;
	int				y;
	int				z;
	uint32_t	c;
} t_vec;

typedef struct s_camera
{
	float	angx;
	float	angz;
	int		shiftx;
	int		shifty;
	float	zoom;
	int		iso;
	int		color;
}	t_camera;

typedef struct s_fdf
{
	char		**argv;
	long		**z;
	long		**c;
	size_t		size_x;
	size_t		size_y;
	long		min_z;
	long		max_z;
	int			error;
	int			fd;
	mlx_t		*mlx;
	mlx_image_t	*image;
	t_vec		vec[2];
	t_camera	cam;
}	t_fdf;

typedef struct s_brsnhm
{
	int	d[2];
	int	s[2];
	int	e[2];
}	t_brsnhm;

t_fdf	*init_fdf(int argc, char *argv[]);
void	free_fdf(t_fdf *fdf);

//bresenham.c bresenham_utils.c
void	ft_plot_lines(t_fdf *fdf, int i, int j);
void    move_vec(int k, t_fdf *fdf, int j, int i);
int 	is_pixel(t_vec r0, t_fdf *fdf);
void    set_bresenham(t_vec r0, t_vec r1, t_brsnhm *brs);
void    bresenham_mod(t_vec r0, t_vec r1, t_fdf *fdf);
uint32_t	color_select(t_brsnhm *brs, t_vec r0, t_vec r1, t_fdf *fdf);

#endif
