/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatsaa-m <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:40:08 by fatsaa-m          #+#    #+#             */
/*   Updated: 2024/10/01 12:40:16 by fatsaa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, char const *src, size_t size)
{
	size_t	a;
	size_t	b;
	size_t	i;
	size_t	j;

	a = ft_strlen(src);
	b = ft_strlen(dst);
	i = 0;
	j = 0;
	while (dst[i] && (i < size))
	{
		i++;
		a++;
	}
	while ((size > b + 1) && (src[j] != '\0'))
	{
		dst[i + j] = src[j];
		j++;
		b++;
	}
	dst[b] = '\0';
	return (a);
}
