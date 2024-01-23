#include "fdf.h"

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

int sizeof_arr(char **str)
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


int	set_size_xy(t_fdf *fdf)
{
	char	*str;
	char	**row;
	int		size_y;

	str = get_next_line(fdf->fd);
	if (!str)
	{
		free(fdf);
		exit(value_err("Error: Empty file\n", 1));
	}
	row = ft_split(str, ' ');
	if (!row)
	{
		free(str);
		free(fdf);
		exit(value_err("Error: malloc ft_split\n", 1));
	}
	fdf->size_x = sizeof_arr(row);
	//remove printf and stdio
	printf("size = %d\n",fdf->size_x);
	while (str)
	{
		str = get_next_line(fdf->fd);
		ft_putstr_fd(str, 1);
	//	dim_y++;
	}
	return (0);
}

t_fdf	*init_fdf(int argc, char *argv[])
{
	t_fdf	*fdf;
	char	*pnt;
	int		dim_y;
	int		dim_x;

	if (argc != 2)
		return(null_err("Error: wrong number of arguments.\n"));
	fdf = (t_fdf *)malloc(sizeof(t_fdf) * 1);
	if (!fdf)
		return(null_err("Error: fdf malloc problem\n"));
	fdf->fd = open(argv[1], O_RDONLY);
	if (fdf->fd == -1)
		return(null_err("Error: can't open file\n"));
	set_size_xy(fdf);
	return (fdf);
}

void    free_int_2d(int **m)
{
    size_t  i;

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
}

int	main(int argc, char *argv[])
{
	t_fdf	*fdf;

	fdf = init_fdf(argc, argv);
	if (!fdf)
		return (1);
	free_fdf(fdf);
	return (0);
}
