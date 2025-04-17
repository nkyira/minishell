/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatsaa-m <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:11:20 by fatsaa-m          #+#    #+#             */
/*   Updated: 2024/10/30 11:11:25 by fatsaa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_unsigned_nbr(unsigned int n, int fd, int *count)
{
	char	p;

	p = ((n % 10) + '0');
	*count = *count + 1;
	if (n / 10 > 0)
	{
		if (ft_unsigned_nbr((n / 10), fd, count) == -1)
			return (-1);
	}
	if (ft_putchar_count(p, fd) == -1)
		return (-1);
	return (*count);
}

int	ft_putnbr_count(int n, int fd, int *count)
{
	char	p;

	p = ((n % 10) * ((n >= 0) - (n < 0)) + '0');
	*count = *count + 1;
	if (n < 0)
	{
		if (ft_putchar_count('-', fd) == -1)
			return (-1);
		*count = *count + 1;
	}
	if (n / 10 != 0)
	{
		if (ft_putnbr_count((n / 10) * ((n >= 0) - (n < 0)), fd, count) == -1)
			return (-1);
	}
	if (ft_putchar_count(p, fd) == -1)
		return (-1);
	return (*count);
}
