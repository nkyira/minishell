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

void	check_token_again(t_token **token)
{
	t_token	*temp;

	temp = *token;
	while (temp && ft_strlen(temp->str) == 0)
	{
		temp = free_search_token(temp);
	}
	*token = temp;
	while (temp)
	{
		if (ft_strlen(temp->str) == 0)
		{
			if (!temp->prev)
				temp = free_search_token(temp);
			else if (temp->prev->type == CMD || temp->prev->type == PIPE)
				temp = free_search_token(temp);
			else
				temp = temp->next;
		}
		else
			temp = temp->next;
	}
}
