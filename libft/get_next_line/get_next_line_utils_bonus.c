/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus_utils                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatsaa-m <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 12:10:50 by fatsaa-m          #+#    #+#             */
/*   Updated: 2024/10/23 12:11:05 by fatsaa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(char const *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

static int	concat(char *tab, char const *str, int d)
{
	int	i;

	i = 0;
	while (str[i])
	{
		tab[d] = str[i];
		i++;
		d++;
	}
	return (d);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*temp;
	size_t	i;

	temp = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!temp)
		return (NULL);
	i = concat(temp, s1, 0);
	i = concat(temp, s2, i);
	temp[i] = '\0';
	return (temp);
}

char	*ft_strchr(char const *s, int letter)
{
	int		i;
	char	*str;

	i = 0;
	str = (char *)s;
	if ((char)letter == '\0')
		return (str + ft_strlen(str));
	while (str[i])
	{
		if ((char)letter == str [i])
			return (str + i + 1);
		i++;
	}
	return (NULL);
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*str;
	size_t	i;

	str = (char *)malloc(size * count);
	if (!str)
		return (NULL);
	i = 0;
	while (i < size)
	{
		str[i] = '\0';
		i++;
	}
	return (str);
}
