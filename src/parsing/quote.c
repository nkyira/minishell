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

char	*init_replace_quote(char *str, int *i, char quote)
{
	char	*temp;

	temp = replace_quote(str + *i, quote);
	if (!temp)
	{
		free(str);
		return (NULL);
	}
	return (temp);
}

char	*new_word_in_token(char	*str, char *temp, int *i)
{
	char	*newstr;

	newstr = copy_end_line(str, temp, size_quote(str + *i + 1, '\"'), '\"');
	*i = *i + ft_strlen(temp);
	free(temp);
	free(str);
	return (newstr);
}

char	*replace_dollar_squote(char *str, int *i, char quote)
{
	char	*temp;
	char	*newstr;
	int		taille;

	temp = init_replace_quote(str, i, quote); //'\''
	if (!temp)
		return (NULL);
	taille = ft_strlen(temp);
	*i = *i + taille;
	newstr = copy_end_line(str, temp, taille, quote);
	free(temp);
	free(str);
	return (newstr);
}

static char	*replace_dollar_dquote(char *str, int *i, t_data *data)
{
	char	*temp;
	char	*newstr;
	int		j;

	temp = init_replace_quote(str, i, '\"');
	if (!temp)
		return (NULL);
	j = 0;
	while (temp[j])
	{
		if (temp[j] == '$')
		{
			temp = replace_path(temp, &j, size_path(temp + j + 1, '$'), data);
			if (!temp)
			{
				free(str);
				return (NULL);
			}
		}
		else
			j++;
	}
	newstr = new_word_in_token(str, temp, i);
	return (newstr);
}

char	*replace_with_quote(char *str, t_data *data, int *i, int *status)
{
	if (*status == DQUOTE)
		str = replace_dollar_dquote(str, i, data);
	else if (*status == SQUOTE)
		str = replace_dollar_squote(str, i, '\'');
	*status = DEFAULT;
	return (str);
}
