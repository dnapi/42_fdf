/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math_f.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apimikov <apimikov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:27:39 by apimikov          #+#    #+#             */
/*   Updated: 2024/01/30 17:30:49 by apimikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_abs_i(int i)
{
	return (i * (i >= 0) - i * (i < 0));
}

int	ft_sign(int i)
{
	return ((i >= 0) - (i < 0));
}

int	ft_max(int a, int b)
{
	return (a * (a >= b) + b * (a < b));
}

int	ft_min(int a, int b)
{
	return (a * (a <= b) + b * (a > b));
}
