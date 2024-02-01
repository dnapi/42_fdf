/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_row.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apimikov <apimikov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 11:04:15 by apimikov          #+#    #+#             */
/*   Updated: 2024/02/01 12:45:48 by apimikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	ft_free_char2d(char **split);

// reading row
int	check_format_z(char *str)
{
	int	i;

	if (!ft_strchr("0987654321+-", (int)str[0]))
		return (1);
	i = 1;
	while (str[i] && str[i] != ',' && str[i] != '\n')
	{
		if (!ft_strchr("0987654321", (int)str[i]))
			return (1);
		i++;
	}
	if ((i == 1 && (str[i - 1] == '+' || str[i - 1] == '-')) || i > 11)
		return (1);
	return (0);
}

void	str_to_long(char **str, long *row, size_t size, t_fdf *fdf)
{
	size_t	i;

	i = -1;
	while (++i < size)
	{
		if (check_format_z(str[i]))
		{
			ft_printf("z value, color = ->%s<-\n", str[i]);
			exit(value_err_free("Error: wrong z value format\n", 1, fdf));
		}
		row[i] = ft_atoil(str[i]);
	}
}

void	str_to_color(char **str, long *row, size_t size, t_fdf *fdf)
{
	size_t	i;
	char	*pnt;

	i = -1;
	while (++i < size)
	{
		pnt = str[i];
		while (*pnt && *pnt != ',')
			pnt++;
		if (*pnt == '\0')
			row[i] = DEFAULTCOLOR;
		else
			row[i] = ft_atoi_hex(pnt + 1);
		if ((row[i] >> 32) > 0 || row[i] < 0)
		{
			ft_printf("color = ->%s<-\n", pnt + 1);
			exit(value_err_free("Error: wrong color format\n", 1, fdf));
		}
	}
}
