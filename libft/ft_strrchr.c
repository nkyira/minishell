/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatsaa-m <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:40:08 by fatsaa-m          #+#    #+#             */
/*   Updated: 2024/10/01 12:40:16 by fatsaa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char const *str, int letter)
{
	int	i;

	i = ft_strlen(str) - 1;
	if ((char)letter == '\0')
		return ((char *)str + (i + 1));
	while (i >= 0)
	{
		if ((char)letter == str[i])
			return ((char *)str + i);
		i--;
	}
	return (NULL);
}
