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

int	ft_putchar_count(char c, int fd)
{
	if (write(fd, &c, 1) == -1)
		return (-1);
	return (1);
}

int	ft_putstr_count(char *s, int fd, int *count)
{
	int	i;

	i = 0;
	if (s == NULL)
	{
		if (write(1, "(null)", 6) == -1)
			return (-1);
		else
			return (*count + 6);
	}
	while (s[i])
	{
		if (ft_putchar_count(s[i], fd) == -1)
		{
			*count = -1;
			break ;
		}
		*count = *count + 1;
		i++;
	}
	return (*count);
}

int	memory(void	*str, int *count)
{
	char	*cases;

	cases = "0123456789abcdef";
	*count = (ft_putstr_count("0x", 1, count));
	if (*count == -1)
		return (-1);
	if (str == NULL)
	{
		if (ft_putchar_count('0', 1) == -1)
			return (-1);
		*count = *count + 1;
	}
	else
	{
		*count = convert((unsigned long)str, 16, count, cases);
	}
	return (*count);
}

int	convert(unsigned long num, int base, int *count, char *cases)
{
	*count = *count + 1;
	if (num / base != 0)
	{
		if (convert(num / base, base, count, cases) == -1)
			return (-1);
		if (ft_putchar_count(cases[num % base], 1) == -1)
			return (-1);
	}
	else
	{
		if (ft_putchar_count(cases[num], 1) == -1)
			return (-1);
	}
	return (*count);
}
