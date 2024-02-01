/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_hex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apimikov <apimikov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 09:00:47 by apimikov          #+#    #+#             */
/*   Updated: 2024/01/31 09:58:30 by apimikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	hex_char2int(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	else if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	else if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	else
		return (-1);
}

long	ft_atoi_hex(const char *str)
{
	long	result;
	long	digit;

	result = 0;
	if (ft_strlen(str) >= 2 && str[0] == '0' && \
		(str[1] == 'x' || str[1] == 'X'))
		str += 2;
	else
		return (-1);
	while (*str != '\0' && *str != '\n')
	{
		digit = hex_char2int(*str);
		if (digit == -1)
			return (-1);
		result = result * 16 + digit;
		str++;
	}
	return (result);
}

/*
int main() {
	char hexString[] = "0xABCD";
	int intValue = ft_atoi_hex(hexString);
	if (intValue != -1) {
		printf("The integer value of %s in \
		hexadecimal is: %d\n", hexString, intValue);
	} else {
		printf("%s is not a valid hexadecimal number.\n", hexString);
	}
	return 0;
}
*/
