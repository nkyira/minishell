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

static int	one_command_builtin(t_command *command)
{
	if (!command->next)
	{
		if (command->command && is_builtin(command->command))
		{
			return (1);
		}
	}
	return (0);
}

static int	more_one_command(t_command *command, t_data *data, int *cpid)
{
	int	prev_fd;

	prev_fd = STDIN_FILENO;
	while (command)
	{
		if (pipe(data->pipefd) == -1)
		{
			error_tube();
			return (-1);
		}
		*cpid = fork();
		if (*cpid == -1)
		{
			error_fork(data);
			return (-1);
		}
		if (*cpid == 0)
			child_process(command, data, prev_fd);
		else
		{
			parent_process(&prev_fd, data, command);
		}
		command = command->next;
	}
	return (1);
}

void	execute(t_data *data)
{
	int			cpid;
	int			stdinfd;
	int			stdoutfd;
	t_command	*command;

	command = data->command;
	stdinfd = 0;
	stdoutfd = 0;
	if (one_command_builtin(command))
	{
		if (command->inputfile)
			stdinfd = dup(STDIN_FILENO);
		if (command->outfile)
			stdoutfd = dup(STDOUT_FILENO);
		exe_one_built(data, command, &stdinfd, &stdoutfd);
		close_fds_one_builtin(command, &stdoutfd, &stdinfd);
		return ;
	}
	if (more_one_command(command, data, &cpid) == -1)
		return ;
	close(data->pipefd[0]);
	get_children(data, cpid);
}
