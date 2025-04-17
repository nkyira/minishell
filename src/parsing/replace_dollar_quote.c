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

static	int	replace_token(t_token *token, t_data *data, int status)
{
	int	i;

	i = 0;
	while (token->str[i])
	{
		status = set_status(status, token->str[i]);
		if (status != DEFAULT)
		{
			token->str = replace_with_quote(token->str, data, &i, &status);
			if (!token->str)
				return (1);
			continue ;
		}
		if (token->str[i] == '$')
		{
			token->str = replace_path(token->str, &i, \
				size_path(token->str + i + 1, '$'), data);
			if (!token->str)
				return (1);
			continue ;
		}
		i++;
	}
	return (0);
}

int	replace(t_data *data)
{
	t_token	*temp;

	temp = data->token;
	while (temp)
	{
		if (temp->type == CMD)
		{
			if (replace_token(temp, data, DEFAULT))
				return (1);
		}
		temp = temp->next;
	}
	return (0);
}
