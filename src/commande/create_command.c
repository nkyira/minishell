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

t_command	*create_command(t_token **token)
{
	t_command	*command;
	t_token		*temp;

	temp = *token;
	command = init_command();
	if (!command)
		return (NULL);
	while (temp && temp->type != PIPE)
	{
		if (temp->type != CMD)
		{
			command = init_file(command, temp);
			temp = temp->next;
		}
		else
		{
			command = init_args_command(command, temp);
		}
		if (!command)
			return (NULL);
		temp = temp->next;
	}
	*token = temp;
	return (command);
}

int	create_commands(t_command **command, t_token *token)
{
	t_token		*temp;
	t_command	*commande;

	commande = *command;
	temp = token;
	if (!temp)
		return (0);
	while (temp)
	{
		if (temp->type == PIPE)
		{
			lastadd_command(command, commande);
			commande = commande->next;
		}
		else
		{
			commande = create_command(&temp);
			if (!commande)
				return (0);
			continue ;
		}
		temp = temp->next;
	}
	lastadd_command(command, commande);
	return (1);
}
