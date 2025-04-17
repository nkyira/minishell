/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatsaa-m <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:40:08 by fatsaa-m          #+#    #+#             */
/*   Updated: 2024/10/01 12:40:16 by fatsaa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	parcour(char a, char const *tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (tab[i] == a)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*temp;
	size_t	i;
	size_t	b;
	size_t	d;

	b = ft_strlen(s1);
	i = 0;
	d = 0;
	while (parcour(s1[i], set) && i < b)
		i++;
	while (b > 0 && parcour(s1[b - 1], set))
		b--;
	if (i >= b)
		i = b;
	temp = malloc(sizeof(char) * (b - i + 1));
	if (!temp)
		return (NULL);
	while (b > i)
	{
		temp[d] = s1[i];
		d++;
		i++;
	}
	temp[d] = '\0';
	return (temp);
}
