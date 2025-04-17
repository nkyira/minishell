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
/*
Bon je parcours ma liste, si je rencontre un separateur alors j'alloue de la
memoire pour recupere la chaine precedente et pour le separateur les deux
en tant que tokens, je fais ainsi jusqu'a la fin du parcours de ma chaine
*/

int	quote_error(char *input)
{
	int	i;
	int	status;

	i = 0;
	status = DEFAULT;
	while (input[i] != '\0')
	{
		if (input[i] == '\'' || input[i] == '\"')
			status = set_status(status, input[i]);
		i++;
	}
	if (status != DEFAULT)
	{
		ft_putendl_fd("unexpected EOF while looking for matching", 2);
		return (1);
	}
	return (0);
}

int	is_separator(char *str, int i)
{
	if (ft_isspace(str[i]))
		return (ESPACE);
	else if (str[i] == '|')
		return (PIPE);
	else if (str[i] == '<' && str[i + 1] == '<')
		return (HEREDOC);
	else if (str[i] == '>' && str[i + 1] == '>')
		return (APPEND);
	else if (str[i] == '<')
		return (INPUT);
	else if (str[i] == '>')
		return (TRUNC);
	else
		return (0);
}

int	token_word(int i, int start, t_data *data)
{
	t_token	*temp;

	temp = init_token(CMD, data->input + start, (i + 1) - start);
	lastadd_token(&data->token, temp);
	if (!temp)
		return (-1);
	return (i);
}

int	token_separator(int i, int type, t_data *data)
{
	t_token	*temp;

	if (type == ESPACE)
		return (i);
	else if (type == HEREDOC || type == APPEND)
	{
		temp = init_token(type, data->input + i, 2);
		lastadd_token(&data->token, temp);
		i = i + 1;
	}
	else
	{
		temp = init_token(type, data->input + i, 1);
		lastadd_token(&data->token, temp);
	}
	if (!temp)
		return (-1);
	return (i);
}

int	separator(t_data *data, char *input, int status)
{
	int	i;
	int	start;
	int	type;

	i = 0;
	start = 0;
	while (input[i] != '\0')
	{
		status = set_status(status, input[i]);
		if (status == DEFAULT)
		{
			type = is_separator(input, i);
			if (!type && (input[i + 1] == '\0' || is_separator(input, i + 1)))
				i = token_word(i, start, data);
			else if (type)
			{
				i = token_separator (i, type, data);
				start = i + 1;
			}
			if (i == -1)
				return (-1);
		}
		i++;
	}
	return (0);
}
