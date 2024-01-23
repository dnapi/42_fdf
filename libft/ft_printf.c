/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apimikov <apimikov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 13:57:57 by apimikov          #+#    #+#             */
/*   Updated: 2024/01/08 10:30:58 by apimikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include "libft.h"

static int	insert_args(const char *s, va_list *ap);
static int	call_function(const char s, va_list *ap);

int	ft_printf(const char *s, ...)
{
	va_list	ap;
	int		len;

	va_start(ap, s);
	len = insert_args(s, &ap);
	va_end(ap);
	return (len);
}

static int	insert_args(const char *s, va_list *ap)
{
	int	len;
	int	flag;

	len = 0;
	while (*s)
	{
		if (*s != '%')
		{
			flag = ft_printchar((int)*s);
			if (flag != 1)
				return (-1);
			len += flag;
		}
		else if (ft_strchr("cspdiuxX%", *(++s)))
		{
			flag = call_function(*s, ap);
			if (flag == -1)
				return (-1);
			len += flag;
		}
		else
			return (-1);
		s++;
	}
	return (len);
}

static int	call_function(const char type, va_list *ap)
{
	if (type == 'c')
		return (ft_printchar(va_arg(*ap, int)));
	else if (type == 's')
		return (ft_printstr(va_arg(*ap, char *)));
	else if (type == 'x')
		return (ft_printbase(va_arg(*ap, unsigned int), "0123456789abcdef"));
	else if (type == 'X')
		return (ft_printbase(va_arg(*ap, unsigned int), "0123456789ABCDEF"));
	else if (type == 'u')
		return (ft_printbase(va_arg(*ap, unsigned int), "0123456789"));
	else if (type == 'd' || type == 'i')
		return (ft_printbase(va_arg(*ap, int), "0123456789"));
	else if (type == 'p')
		return (ft_printbase_ulong((unsigned long long)va_arg(*ap, void *), \
			"0123456789abcdef"));
	else if (type == '%')
		return (ft_printchar('%'));
	return (-1);
}
