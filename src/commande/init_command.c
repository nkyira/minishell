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

t_command	*init_command(void)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	if (!command)
	{
		ft_putendl_fd(strerror(errno), 2);
		return (NULL);
	}
	command->args = NULL;
	command->outfile = NULL;
	command->inputfile = NULL;
	command->next = NULL;
	command->prev = NULL;
	command->command = NULL;
	command->infile = -2;
	command->ofile = -2;
	return (command);
}

t_redict	*init_redirect(int type, char *file)
{
	t_redict	*temp;

	temp = malloc(sizeof(t_redict));
	if (!temp)
	{
		ft_putendl_fd(strerror(errno), 2);
		return (NULL);
	}
	temp->file = ft_strdup(file);
	if (!temp->file)
	{
		perror(temp->file);
		free(temp);
		return (NULL);
	}
	temp->type = type;
	temp->next = (NULL);
	return (temp);
}

void	check_error_file(t_token *token, t_command *command, int *fd)
{
	if (command->ofile != -1 && command->infile != -1)
	{
		if (*fd != -2)
			close(*fd);
		*fd = infile(token);
	}
}

t_command	*init_file(t_command *command, t_token *token)
{
	t_redict	*temp;

	temp = init_redirect(token->type, token->next->str);
	if (!temp)
	{
		ft_putendl_fd(strerror(errno), 2);
		free_command(command);
		return (NULL);
	}
	if (token->type == TRUNC || token->type == APPEND)
	{
		check_error_file(token, command, &command->ofile);
	}
	else if (token->type == HEREDOC || token->type == INPUT)
	{	
		check_error_file(token, command, &command->infile);
	}
	return (command);
}

t_command	*init_args_command(t_command *command, t_token *token)
{
	char	*temp;

	temp = ft_strdup(token->str);
	if (!temp)
	{
		perror(temp);
		free_command(command);
		return (NULL);
	}
	if (command->command == NULL)
	{
		command->command = ft_strdup(token->str);
		command->args = ft_calloc(sizeof(char *), (size_args(token) + 1));
		if (!command->command || !command->args)
		{
			strerror(errno);
			free_command(command);
			return (NULL);
		}
		lastadd_arg(command->args, temp);
		return (command);
	}
	lastadd_arg(command->args, temp);
	return (command);
}
