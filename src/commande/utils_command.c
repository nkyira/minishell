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

static	t_command	*ft_lastcommand(t_command *command, int *i)
{
	t_command	*temp;

	temp = command;
	if (!temp)
		return (NULL);
	while (temp->next)
	{
		*i = *i + 1;
		temp = temp->next;
	}
	return (temp);
}

void	lastadd_command(t_command **command, t_command *newcommand)
{
	t_command	*temp;
	int			i;

	i = 1;
	if (!command)
		return ;
	temp = ft_lastcommand(*command, &i);
	if (!temp)
		*command = newcommand;
	else
	{
		temp->next = newcommand;
		temp->next->prev = temp;
	}
}

static	t_redict	*ft_lastredirect(t_redict *redirect, int *i)
{
	t_redict	*temp;

	temp = redirect;
	if (!temp)
		return (NULL);
	while (temp->next)
	{
		*i = *i + 1;
		temp = temp->next;
	}
	return (temp);
}

void	lastadd_redirect(t_redict **redirect, t_redict *newredirect)
{
	t_redict	*temp;
	int			i;

	i = 1;
	temp = ft_lastredirect(*redirect, &i);
	if (!temp)
		*redirect = newredirect;
	else
	{
		temp->next = newredirect;
	}
}

int	is_not_redirection(t_token *token)
{
	if (!token)
		return (1);
	if (token->type == PIPE || token->type == CMD)
	{
		return (1);
	}
	return (0);
}
