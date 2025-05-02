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

void	free_redirect(t_redict *redirect)
{
	if (redirect->file)
		free(redirect->file);
	free(redirect);
}

void	free_redirects(t_redict *redirect)
{
	t_redict	*temp;
	t_redict	*prev;

	temp = redirect;
	prev = redirect;
	while (temp)
	{
		temp = prev->next;
		free_redirect(prev);
		prev = temp;
	}
}

void	free_command(t_command *command)
{
	if (command->command)
		free(command->command);
	free_redirects(command->outfile);
	free_redirects(command->inputfile);
	free_arg(command->args);
	free(command);
}

void	free_commands(t_command *command)
{
	t_command	*temp;
	t_command	*prev;

	temp = command;
	prev = temp;
	while (temp)
	{
		temp = prev->next;
		free_command(prev);
		prev = temp;
	}
}
