/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_size.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apimikov <apimikov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 11:03:19 by apimikov          #+#    #+#             */
/*   Updated: 2024/02/01 11:03:38 by apimikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

//  first reading file -> setting size of map
static size_t	sizeof_arr(char **str)
{
	size_t	i;

	if (!str)
		return (-1);
	i = 0;
	while (str[i])
	{
		if (*str[i] == '\n')
			break ;
		i++;
	}
	return (i);
}

static size_t	sizeof_line(char *str)
{
	char	**row;
	size_t	size;

	if (!str)
		return (-1);
	row = ft_split(str, ' ');
	if (!row)
		exit(value_err_free("Error: malloc ft_split\n", 1, NULL));
	size = sizeof_arr(row);
	ft_free_char2d(row);
	return (size);
}

int	set_size_xy(t_fdf *fdf)
{
	char	*str;

	fdf->fd = open(fdf->argv[1], O_RDONLY);
	if (fdf->fd == -1)
		exit (value_err_free("Error: can't open file\n", 1, fdf));
	str = get_next_line(fdf->fd);
	if (!str)
		exit(value_err_free("Error: Empty file\n", 1, fdf));
	fdf->size_x = sizeof_line(str);
	free(str);
	fdf->size_y = 1;
	while (str)
	{
		str = get_next_line(fdf->fd);
		if (!str)
			break ;
		if (fdf->size_x != sizeof_line(str))
			exit(value_err_free("Error: wrong format of the file\n", 1, fdf));
		free(str);
		fdf->size_y++;
	}
	if (close(fdf->fd) == -1)
		exit(value_err_free("Error: close file error\n", 1, fdf));
	return (0);
}
