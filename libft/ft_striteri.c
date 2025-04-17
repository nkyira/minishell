/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                       :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: fatsaa-m <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:40:08 by fatsaa-m          #+#    #+#             */
/*   Updated: 2024/10/01 12:40:16 by fatsaa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned long	i;
	unsigned long	l;

	l = ft_strlen(s);
	i = 0;
	while (i < l)
	{
		(*f)(i, s);
		++i;
		s++;
	}
}
