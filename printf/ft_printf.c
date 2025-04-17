/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatsaa-m <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:11:20 by fatsaa-m          #+#    #+#             */
/*   Updated: 2024/11/01 16:00:45 by fatsaa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	choice(const char *p, va_list arg)
{
	int	val;

	val = 0;
	if (*p == '%')
		val = ft_putchar_count('%', 1);
	else if (*p == 'c')
		val = ft_putchar_count(va_arg(arg, int), 1);
	else if (*p == 'd')
		val = ft_putnbr_count(va_arg(arg, int), 1, &val);
	else if (*p == 's')
		val = ft_putstr_count(va_arg(arg, char *), 1, &val);
	else if (*p == 'u')
		val = ft_unsigned_nbr(va_arg(arg, unsigned int), 1, &val);
	else if (*p == 'i')
		val = ft_putnbr_count(va_arg(arg, int), 1, &val);
	else if (*p == 'p')
		memory(va_arg(arg, void *), &val);
	else if (*p == 'x')
		val = convert(va_arg(arg, unsigned int), 16, &val, "0123456789abcdef");
	else if (*p == 'X')
		val = convert(va_arg(arg, unsigned int), 16, &val, "0123456789ABCDEF");
	return (val);
}

int	count_error(const char *p, va_list arg, int count)
{
	int	number;

	number = choice(p, arg);
	if (number == -1)
		return (-1);
	else
		return (count + number);
}

int	ft_printf(const char *p, ...)
{
	va_list	arg;
	int		count;

	va_start(arg, p);
	count = 0;
	while (*p != '\0')
	{
		if (*p == '%')
		{
			p++;
			count = count_error(p, arg, count);
		}
		else
		{
			count++;
			if (ft_putchar_count(*p, 1) == -1)
				count = -1;
		}
		if (count == -1)
			break ;
		p++;
	}
	va_end(arg);
	return (count);
}
