/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apimikov <apimikov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:43:29 by apimikov          #+#    #+#             */
/*   Updated: 2024/01/16 10:05:03 by apimikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	word_count_char(char const *s, char c);
int		write_word_char(char **arr, char const **s, char c);
void	clean_array(char ***arr, size_t len);

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	len;
	char	**array;

	if (!s)
		return (NULL);
	len = word_count_char(s, c);
	array = (char **)malloc((len + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	i = 0;
	while (*s && i < len)
	{
		while ((*s == c) && *s)
			s++;
		if (!write_word_char(array + i, &s, c))
		{
			clean_array(&array, i);
			return (NULL);
		}
		i++;
	}
	*(array + len) = NULL;
	return (array);
}

void	clean_array(char ***arr, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		free(*(*arr + i));
		i++;
	}
	free(*arr);
}

int	write_word_char(char **arr, char const **s, char c)
{
	char const	*temp;
	int			len;
	int			i;

	temp = *s;
	len = 0;
	while ((*temp != c) && *temp)
	{
		len++;
		temp++;
	}
	if (len > 0)
	{
		*arr = (char *)malloc(sizeof(char) * (len + 1));
		if (*arr == NULL)
			return (0);
	}
	i = -1;
	while (++i < len)
	{
		(*arr)[i] = **s;
		(*s)++;
	}
	(*arr)[i] = '\0';
	return (1);
}

size_t	word_count_char(char const *s, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			i++;
			continue ;
		}
		count++;
		while ((s[i] != c) && s[i])
			i++;
	}
	return (count);
}

/*
int	is_sep(char c, char *charset)
{
	while (*charset)
	{
		if (*charset == c)
			return (1);
		charset++;
	}
	return (0);
}
*/
