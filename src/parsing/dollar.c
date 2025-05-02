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

static	void	just_for_norminette(char *str, int *i, int taille)
{
	*i = taille + *i;
	free(str);
}

static char	*init_char(char *str, int size)
{
	char	*newstr;

	newstr = malloc(sizeof(char) * size);
	if (!newstr)
	{
		ft_putendl_fd(strerror(errno), 2);
		free(str);
		return (NULL);
	}
	return (newstr);
}

static char	*replace_path_util(char *str, int *i, int size_word, t_data *data)
{
	char	*path;
	char	*newstr;
	int		taille;
	int		j;

	path = search_env(str + *i + 1, data, size_word);
	newstr = init_char(str, init_size_path(path, str, &taille, size_word));
	if (!newstr)
		return (NULL);
	j = 0;
	while (str[j])
	{
		if (str[j] == '$' && j == *i)
		{
			if (path)
				ft_strlcpy(newstr + j, path, taille + 1);
			break ;
		}
		newstr[j] = str[j];
		j++;
	}
	free(path);
	copy_chaine(newstr, str, j + size_word + 1, j + taille);
	just_for_norminette(str, i, taille);
	return (newstr);
}

char	*replace_path(char *str, int *i, int size_word, t_data *data)
{
	if (!str[*i + 1] || isspace(str[*i +1]))
	{
		*i = *i + 1;
		return (str);
	}
	if (str[*i + 1] && str[*i + 1] == '\"')
	{
		*i = *i + 1;
		return (str);
	}
	return (replace_path_util(str, i, size_word, data));
}
