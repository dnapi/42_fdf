/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fdf_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apimikov <apimikov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:23:37 by apimikov          #+#    #+#             */
/*   Updated: 2024/02/01 16:25:31 by apimikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf_bonus.h"

int	file_name_check(char *argv[])
{
	int	len;

	len = ft_strlen(argv[1]);
	ft_printf("file extension is \"%s\".\n",argv[1] + len -4);
	if (ft_strncmp(argv[1] + len - 4, ".fdf", 4))
		return (1);
	return (0);
}

// initialization of fdf structure
t_fdf	*init_fdf(int argc, char *argv[])
{
	t_fdf	*fdf;
	char	*pnt;

	if (argc != 2)
		return (null_err("Error. fdf: wrong number of arguments.\n"));
	if (file_name_check(argv))
		return (null_err("Error. fdf: wrong extension of the file.\n"));
	fdf = (t_fdf *)malloc(sizeof(t_fdf) * 1);
	if (!fdf)
		return (null_err("Error. fdf: malloc problem\n"));
	fdf->argv = argv;
	// is it good practice ?
	//fdf->z = NULL;
	//fdf->c = NULL;
	if (fdf->z == NULL)
		ft_printf("Hi fdf->z is NULL at initialization!\n");
	else
		ft_printf("Hi fdf->z is NOT NULL at initialization!\n");
	set_size_xy(fdf);
	fdf->fd = open(argv[1], O_RDONLY);
	// fix potential leaks in cas of error ?
	if (fdf->fd == -1)
		return ((t_fdf *)(uintptr_t)value_err_free("fdf:can'topenfile\n", 0, fdf));
	set_z_matrix(fdf);
	set_z_minmax(fdf);
	set_camera(fdf);
	return (fdf);
}

void	ft_free_char2d(char **split)
{
	size_t	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		split[i] = NULL;
		i++;
	}
	free(split);
//	split = NULL;
}

void	free_int_2d(long **m, size_t sizey)
{
	size_t	i;

	//remove next two lines
	if (m)
		ft_printf("Hi! you free it ! I am not NULL!!!\n");
	// till here
	if (!m)
		return ;
	i = 0;
	while (i < sizey)
	{
		if (m[i])
		{
			free(m[i]);
			m[i] = NULL;
		}
		i++;
	}
	free(m);
	//m = NULL;
}

void	free_fdf(t_fdf *fdf)
{
	if (!fdf)
		return ;
	free_int_2d(fdf->z, fdf->size_y);
	fdf->z = NULL;
	free_int_2d(fdf->c, fdf->size_y);
	fdf->c = NULL;
	free(fdf);
//	fdf = NULL;
}
