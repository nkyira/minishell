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

void	close_fds_one_builtin(t_command *command, int *stdoutfd, int *stdinfd)
{
	if (command->inputfile)
	{
		dup2(*stdinfd, STDIN_FILENO);
		close(*stdinfd);
	}
	if (command->outfile)
	{
		dup2(*stdoutfd, STDOUT_FILENO);
		close(*stdoutfd);
	}
}

int	is_builtin(char *command)
{
	if (!command)
		return (0);
	if (ft_strncmp(command, "exit", ft_max(ft_strlen(command), 4)) == 0)
		return (1);
	if (ft_strncmp(command, "pwd", ft_max(ft_strlen(command), 3)) == 0)
		return (1);
	if (ft_strncmp(command, "cd", ft_max(ft_strlen(command), 2)) == 0)
		return (1);
	if (ft_strncmp(command, "export", ft_max(ft_strlen(command), 6)) == 0)
		return (1);
	if (ft_strncmp(command, "echo", ft_max(ft_strlen(command), 4)) == 0)
		return (1);
	if (ft_strncmp(command, "unset", ft_max(ft_strlen(command), 5)) == 0)
		return (1);
	if (ft_strncmp(command, "env", ft_max(ft_strlen(command), 3)) == 0)
		return (1);
	return (0);
}

void	execute_builtin(t_data *data, t_command *command)
{
	if (ft_strncmp(command->command, "exit", 4) == 0)
		exit_builtin(data, command->args);
	else if (ft_strncmp(command->command, "pwd", 3) == 0)
		pwd_builtin(data, command->args);
	else if (ft_strncmp(command->command, "echo", 4) == 0)
		echo_builtin(command->args);
	else if (ft_strncmp(command->command, "cd", 2) == 0)
		cd_builtin(data, command->args);
	else if (ft_strncmp(command->command, "export", 6) == 0)
		export_builtin(data, command->args);
	else if (ft_strncmp(command->command, "unset", 5) == 0)
		unset_builtin(data, command->args);
	else if (ft_strncmp(command->command, "env", 3) == 0)
		env_builtin(data, command->args);
}
