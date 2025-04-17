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
	initialisation de token et ajout a la liste
*/
t_token	*init_token(int type, char *str, int size)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
	{
		ft_putendl_fd(strerror(errno), 2);
		return (NULL);
	}
	token->type = type;
	token->str = malloc(sizeof(char) * (size + 1));
	if (!token->str)
	{
		perror(token->str);
		free(token);
		return (NULL);
	}
	ft_strlcpy(token->str, str, size + 1);
	token->next = NULL;
	token->prev = NULL;
	token->index = 0;
	return (token);
}

t_token	*ft_lasttoken(t_token *token, int *i)
{
	t_token	*temp;

	temp = token;
	if (!temp)
		return (NULL);
	while (temp->next)
	{
		*i = *i + 1;
		temp = temp->next;
	}
	return (temp);
}

void	lastadd_token(t_token **token, t_token *newtoken)
{
	t_token	*temp;
	int		i;

	i = 1;
	temp = ft_lasttoken(*token, &i);
	if (!newtoken)
		return ;
	if (!temp)
		*token = newtoken;
	else
	{
		temp->next = newtoken;
		temp->next->prev = temp;
		temp->next->index = i;
	}
}
