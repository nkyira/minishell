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

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r'
		|| c == '\v' || c == '\f')
		return (c);
	return (0);
}

int	set_status(int status, char character)
{
	if (character == '\'' && status == DEFAULT)
		status = SQUOTE;
	else if (character == '\"' && status == DEFAULT)
		status = DQUOTE;
	else if (character == '\'' && status == SQUOTE)
		status = DEFAULT;
	else if (character == '\"' && status == DQUOTE)
		status = DEFAULT;
	return (status);
}

int	size_word_quote(char *str, char quote)
{
	int	i;

	i = 1;
	while (str[i] != quote && str[i])
	{
		i++;
	}
	return (i);
}

char	*replace_quote(char	*str, char quote)
{
	char	*temp;
	int		i;
	size_t	len;

	len = size_word_quote(str, quote);
	temp = malloc(sizeof(char) * len);
	if (!temp)
	{
		perror(temp);
		return (NULL);
	}
	i = 1;
	while (str[i] != quote && str[i])
	{
		temp[i - 1] = str[i];
		i++;
	}
	temp[i - 1] = '\0';
	return (temp);
}

int	special_character(int caractere)
{
	if (caractere == '_')
		return (0);
	if (caractere >= 48 && caractere <= 57)
		return (0);
	if (caractere >= 65 && caractere <= 90)
		return (0);
	if (caractere >= 97 && caractere <= 122)
		return (0);
	return (1);
}
