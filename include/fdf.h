/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apimikov <apimikov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 07:20:43 by apimikov          #+#    #+#             */
/*   Updated: 2024/02/01 15:45:21 by apimikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

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

# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include "libft.h"
# include "MLX42.h"

typedef struct s_vec
{
	int			x;
	int			y;
	int			z;
	uint32_t	c;
}	t_vec;

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

//main.c
t_fdf		*init_fdf(int argc, char *argv[]);
void		free_fdf(t_fdf *fdf);
void		ft_free_char2d(char **split);

//bresenham.c bresenham_utils.c
void		ft_plot_lines(t_fdf *fdf, int i, int j);
void		move_vec(int k, t_fdf *fdf, int j, int i);
int			is_pixel(t_vec r0, t_fdf *fdf);
void		set_bresenham(t_vec r0, t_vec r1, t_brsnhm *brs);
void		bresenham_mod(t_vec r0, t_vec r1, t_fdf *fdf);
uint32_t	color_select(t_brsnhm *brs, t_vec r0, t_vec r1, t_fdf *fdf);

//hooks.c
void		ft_hook_image(void *data);
void		ft_hook_key(void *fdf);
void		keyhook_event(mlx_key_data_t keydata, void *data);
void		ft_hook_print(void *data);

//error_msg.c
void		*null_err(char *msg);
int			value_err(char *msg, int err);
int			value_err_free(char *msg, int err, t_fdf *fdf);

//set_size.c
int			set_size_xy(t_fdf *fdf);

//init_fdf_utils.c
void		init_zc_matrices(t_fdf *fdf);
void		set_z_matrix(t_fdf *fdf);
void		set_z_minmax(t_fdf *fdf);
void		set_camera(t_fdf *fdf);

//read_row.c
void		str_to_long(char **str, long *row, size_t size, t_fdf *fdf);
void		str_to_color(char **str, long *row, size_t size, t_fdf *fdf);

#endif
