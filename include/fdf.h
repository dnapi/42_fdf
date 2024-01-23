/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apimikov <apimikov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 07:20:43 by apimikov          #+#    #+#             */
/*   Updated: 2024/01/23 10:42:58 by apimikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H


#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "libft.h"
#include "get_next_line.h"

typedef struct s_fdf
{
	char	**argv;
	int		**z;
	int		**c;
	int		size_x;
	int		size_y;
	int		error;
	int		fd;
}	t_fdf;

#endif
