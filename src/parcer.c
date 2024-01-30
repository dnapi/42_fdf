#include "../include/fdf.h"

void	ft_free_char2d(char **split);

// error msgs
void	*null_err(char *msg)
{
	ft_putstr_fd(msg, 2);
	return (NULL);
}

int	value_err(char *msg, int err)
{
	ft_putstr_fd(msg, 2);
	return (err);
}

int	value_err_free(char *msg, int err, t_fdf *fdf)
{
	free(fdf);
	ft_putstr_fd(msg, 2);
	return (err);
}

//  first reading file -> setting size of map
size_t	sizeof_arr(char **str)
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

size_t	sizeof_line(char *str)
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

// init z matrix
int	**alloc_2d_int(size_t size_x, size_t size_y)
{
	int	**z;
	int	i;
	int	x;

	z = (int **)malloc(sizeof(int *) * size_y);
	if (!z)
		return (null_err("Error: memory problem \n"));
	i = -1;
	while (++i < size_y)
	{
		z[i] = (int *)malloc(sizeof(int) * size_x);
		if (!z[i])
		{
			while (--i >= 0)
				free(z[i]);
			free(z);
			return (null_err("Error: memory problem \n"));
		}
		x = -1;
		while (++x < size_x)
			z[i][x] = 0;
	}
	return (z);
}

void	str_to_int(char **str, int *row, size_t size)
{
	size_t	i;

	i = -1;
	while (++i < size)
		row[i] = ft_atoi(str[i]);
}

void	print_array_1d(int *row, size_t size)
{
	size_t	i;

	i = -1;
	while (++i < size)
	{
		ft_putnbr_fd(row[i], 1);
		ft_putstr_fd(" ", 1);
	}
	ft_putstr_fd("\n", 1);
}

void	set_z_matrix(t_fdf *fdf)
{
	char	*str;
	char	**row;
	size_t	y;

	fdf->z = alloc_2d_int(fdf->size_x, fdf->size_y);
	if (!fdf->z)
		exit(value_err_free("Error: malloc alloc_2d_int\n", 1, fdf));
	if (!fdf->z)
		exit(value_err_free("Error: memory problem\n", 1, fdf));
	y = -1;
	while (++y < fdf->size_y)
	{
		str = get_next_line(fdf->fd);
		if (!str)
			break ;
		row = ft_split(str, ' ');
		free(str);
		str_to_int(row, fdf->z[y], fdf->size_x);
		ft_free_char2d(row);
	}
	if (close(fdf->fd) == -1)
		exit(value_err_free("Error: close file error\n", 1, fdf));
	return ;
}

void	set_z_minmax(t_fdf *fdf)
{
	size_t	i;
	size_t	j;
	int		z[2];

	z[0] = 0;
	z[1] = 0;
	j = -1;
	while (++j < fdf->size_y)
	{
		i = -1;
		while (++i < fdf->size_x)
		{
			z[0] = ft_min(z[0], fdf->z[j][i]);
			z[1] = ft_max(z[1], fdf->z[j][i]);
		}
	}
	fdf->min_z = z[0];
	fdf->max_z = z[1];
}

void	set_camera(t_fdf *fdf)
{
	fdf->cam.iso = 1;
	fdf->cam.angz = 3.1415 / 4;
	fdf->cam.angx = 0.95531;
	fdf->cam.shiftx = 0;
	fdf->cam.shifty = 0;
	fdf->cam.zoom = 1;
}

//  init_fdf 

t_fdf	*init_fdf(int argc, char *argv[])
{
	t_fdf	*fdf;
	char	*pnt;
	int		dim_y;
	int		dim_x;

	if (argc != 2)
		return (null_err("Error: wrong number of arguments.\n"));
	fdf = (t_fdf *)malloc(sizeof(t_fdf) * 1);
	if (!fdf)
		return (null_err("Error: fdf malloc problem\n"));
	fdf->argv = argv;
	set_size_xy(fdf);
	fdf->fd = open(argv[1], O_RDONLY);
	if (fdf->fd == -1)
		return (null_err("Error: can't open file\n"));
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
		i++;
	}
	free(split);
}

void	free_int_2d(int **m)
{
	size_t	i;

	i = 0;
	while (m[i])
	{
		free(m[i]);
		i++;
	}
	free(m);
}

void	free_fdf(t_fdf *fdf)
{
	if (!fdf)
		return ;
	if (!fdf->z)
		free_int_2d(fdf->z);
	free(fdf);
}
