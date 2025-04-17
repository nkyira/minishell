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

int	size_args(t_token *token)
{
	t_token	*temp;
	int		size;

	temp = token;
	size = 0;
	while (temp && temp->type != PIPE)
	{
		if (temp->type == CMD && is_not_redirection(temp->prev))
			size++;
		temp = temp->next;
	}
	return (size);
}

void	lastadd_arg(char **str, char *word)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	str[i] = word;
}
