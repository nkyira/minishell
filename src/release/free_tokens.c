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

void	free_token(t_token *token)
{
	if (token->str)
		free(token->str);
	free(token);
}

void	free_tokens(t_token *token)
{
	t_token	*temp;
	t_token	*prev;

	temp = token;
	prev = token;
	while (temp)
	{
		temp = prev->next;
		free_token(prev);
		prev = temp;
	}
}

void	free_arg(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

t_token	*free_search_token(t_token *token)
{
	t_token	*temp;
	t_token	*next;

	temp = token;
	if (temp->prev)
		temp->prev->next = temp->next;
	if (temp->next)
		temp->next->prev = temp->prev;
	next = temp->next;
	free_token(temp);
	return (next);
}
