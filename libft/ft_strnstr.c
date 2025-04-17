/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatsaa-m <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:40:08 by fatsaa-m          #+#    #+#             */
/*   Updated: 2024/10/01 12:40:16 by fatsaa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char const *str1, char const *str2, size_t len)
{
	size_t	d;
	size_t	i;
	size_t	j;

	i = 0;
	if (str2[0] == '\0')
		return ((char *)str1);
	if ((ft_strlen(str2) > len && str1) || ft_strlen(str2) > ft_strlen(str1))
		return (0);
	while ((i < len) && str1[i])
	{
		j = 0;
		d = i;
		while (str2[j] != '\0' && (d + j) < len)
		{
			if (str1[d + j] != str2[j])
				break ;
			j++;
		}
		if (str2[j] == '\0')
			return ((char *)str1 + i);
		i++;
	}
	return (0);
}
