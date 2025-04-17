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
	-si l'input commence par '|' renvoyer une erreur
	-s'il ya une commande speciale consecutive renvoyer une erreur
	-si l'input se termine par une commande speciale renvoyer une erreur
*/
int	special_consecutive(t_token *token)
{
	if (!token)
	{
		printf("parse error near `\\n'\n");
		return (1);
	}
	else if (token->type == CMD)
		return (0);
	else if (token->prev->type == PIPE && token->type != PIPE)
		return (0);
	printf("parse error near `%s'\n", token->str);
	return (1);
}

int	check_tokens(t_token *tokens)
{
	t_token	*temp;

	temp = tokens;
	if (temp->type == PIPE)
	{
		ft_putendl_fd("parse error near `|'", 2);
		return (0);
	}
	while (temp)
	{
		if (temp->type != CMD)
		{
			if (special_consecutive(temp->next))
				return (0);
		}
		temp = temp->next;
	}
	return (1);
}
