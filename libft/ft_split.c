/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatsaa-m <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:40:08 by fatsaa-m          #+#    #+#             */
/*   Updated: 2024/10/01 12:40:16 by fatsaa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_size(char const *tab, char a, int b, int c)
{
	int	i;
	int	d;

	i = 0;
	d = 0;
	if (tab[0] != a && b > 0)
	{
		d = 1;
		i = 1;
	}
	while (i < b)
	{
		if (tab[i] == a && tab[i + 1] != a && tab[i + 1] != '\0')
		{
			d++;
		}
		if (tab[i] == a && c == 1)
			break ;
		i++;
	}
	if (c == 1)
		return (i + 1);
	return (d + 1);
}

static int	element(char *str, char const *tab, char a, int b)
{
	int	i;

	i = 0;
	while (tab[b] != a && tab[b])
	{
		str[i] = tab[b];
		i++;
		b++;
	}
	str[i] = '\0';
	return (b);
}

static void	ft_free(char **temp, int d)
{
	int	i;

	i = 0;
	while (i < d)
	{
		free(temp[i]);
		i++;
	}
	free(temp);
}

static char	**print(char const *s, char c, int i, int d)
{
	int		e;
	char	**temp;

	e = ft_strlen(s);
	temp = malloc(sizeof(char *) * (ft_size(s, c, e, 0)));
	if (!temp)
		return (NULL);
	while (s[i])
	{
		if (s[i] == c)
		{
			i++;
			continue ;
		}
		temp[d] = malloc(sizeof(char) * (ft_size(s + i, c, e - i, 1)));
		if (!temp[d])
		{
			ft_free(temp, d);
			return (NULL);
		}
		i = element(temp[d], s, c, i);
		d++;
	}
	temp[d] = NULL;
	return (temp);
}

char	**ft_split(char const *s, char c)
{
	char	**temp;
	int		i;
	int		d;

	i = 0;
	d = 0;
	temp = print(s, c, i, d);
	return (temp);
}
