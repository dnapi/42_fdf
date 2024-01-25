/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apimikov <apimikov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 07:20:43 by apimikov          #+#    #+#             */
/*   Updated: 2024/01/25 17:49:40 by apimikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#define IMAGEWIDTH 100
#define IMAGEHEIGHT 100
#define MLXWIDTH 500
#define MLXHEIGHT 500

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "libft.h"
#include "MLX42.h"
#include "get_next_line.h"

typedef struct s_fdf
{
	char		**argv;
	int			**z;
	int			**c;
	size_t		size_x;
	size_t		size_y;
	int			error;
	int			fd;
	mlx_t		*mlx;
	mlx_image_t	*image;
	int			temp;	
}	t_fdf;

typedef struct s_vec_2d
{
	int	x;
	int y;
	uint32_t color;
}	t_vec_2d;

#endif
