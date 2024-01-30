/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apimikov <apimikov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 07:20:43 by apimikov          #+#    #+#             */
/*   Updated: 2024/01/30 17:59:11 by apimikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

//#include <cstdint>
# define IMAGEWIDTH 1100
# define IMAGEHEIGHT 1100
# define MLXWIDTH 1200
# define MLXHEIGHT 1200
# define IMAGEBACKGROUND 0xff0000ff 
# define CHANNELBACK 100 

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <math.h>
# include "libft.h"
# include "MLX42.h"
# include "get_next_line.h"

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
}	t_camera;

typedef struct s_fdf
{
	char				**argv;
	int					**z;
	int					**c;
	size_t			size_x;
	size_t			size_y;
	int					min_z;
	int					max_z;
	int					error;
	int					fd;
	mlx_t				*mlx;
	mlx_image_t	*image;
	t_vec				vec[2];
	t_camera		cam;
}	t_fdf;

typedef struct s_brsnhm
{
	int	d[2];
	int	s[2];
	int	e[2];
}	t_brsnhm;

t_fdf	*init_fdf(int argc, char *argv[]);
void	free_fdf(t_fdf *fdf);

//bresenham.c
void    move_vec(int k, t_fdf *fdf, int j, int i);
int 	is_pixel(t_vec r0, t_fdf *fdf);
void    set_bresenham(t_vec r0, t_vec r1, t_brsnhm *brs);
void    bresenham_mod(t_vec r0, t_vec r1, t_fdf *fdf);

//ft_math  functions  -> moved to libft
//int		ft_abs(int i);
//int		ft_sign(int i);
//int		ft_min(int a, int b);
//int		ft_max(int a, int b);

#endif
