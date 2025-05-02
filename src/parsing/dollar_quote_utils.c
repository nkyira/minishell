/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatsaa-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:46:24 by fatsaa-m          #+#    #+#             */
/*   Updated: 2025/04/08 15:46:38 by fatsaa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	copy_chaine(char *str, char *val, int i, int n)
{
	while (val[i])
	{
		str[n] = val[i];
		n++;
		i++;
	}
	str[n] = '\0';
}

int	init_size_path(char *path, char *str, int *taille, int size_word)
{
	int	len;

	if (!path)
		*taille = 0;
	else
		*taille = ft_strlen(path);
	len = ft_strlen(str) - size_word + *taille;
	return (len);
}

int	size_path(char *str, char caracter)
{
	int	i;

	i = 0;
	if (str[i] && str[i] == '$')
		return (1);
	if (str[i] && str[i] == '?')
		return (1);
	while (str[i] && str[i] != caracter && !special_character(str[i]))
	{
		i++;
	}
	return (i);
}

int	size_quote(char *str, char character)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != character)
	{
		i++;
	}
	return (i);
}

char	*copy_end_line(char *str, char *path, int size_word, char quote)
{
	char	*newstr;
	int		j;
	int		taille;

	taille = ft_strlen(path);
	newstr = malloc(sizeof(char) * (ft_strlen(str) - size_word + taille - 1));
	if (!newstr)
	{
		perror(newstr);
		return (NULL);
	}
	j = 0;
	while (str[j])
	{
		if (str[j] == quote)
		{
			ft_strlcpy(newstr + j, path, taille + 1);
			break ;
		}
		newstr[j] = str[j];
		j++;
	}
	copy_chaine(newstr, str, j + size_word + 2, j + taille);
	return (newstr);
}
