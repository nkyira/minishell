/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatsaa-m <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:40:08 by fatsaa-m          #+#    #+#             */
/*   Updated: 2024/10/01 12:40:16 by fatsaa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_size(int n)
{
	int	i;

	if (n == 0)
		return (1);
	if (n < 0)
		i = 1;
	else
		i = 0;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*number;
	int		i;

	i = ft_size(n);
	number = malloc(sizeof(char) * (i + 1));
	if (!number)
		return (NULL);
	if (n < 0)
		number[0] = '-';
	if (n == 0)
		number[0] = '0';
	number[i] = '\0';
	while (n != 0)
	{
		number[i - 1] = ((n % 10) * ((n >= 0) - (n < 0)) + '0');
		n = n / 10;
		i--;
	}
	return (number);
}
