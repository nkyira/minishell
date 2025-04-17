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

static char	**split_path(t_data *data)
{
	char	**paths;
	char	*path;

	path = ft_strdup(search_env("PATH", data, 4));
	if (!path)
	{
		perror(path);
		return (NULL);
	}
	paths = ft_split(path, ':');
	free(path);
	if (!paths)
		return (NULL);
	return (paths);
}

static char	*join_path(char *path, char *str)
{
	char	*temp;
	char	*newpath;

	temp = ft_strjoin(path, "/");
	if (!temp)
		return (NULL);
	newpath = ft_strjoin(temp, str);
	free(temp);
	if (!newpath)
		return (NULL);
	return (newpath);
}

static char	*command_path_utils(t_command *command, t_data *data, char **paths)
{
	int		i;
	char	*path_access;

	i = 0;
	while (paths[i])
	{
		path_access = join_path(paths[i], command->command);
		if (!path_access)
			return (NULL);
		if (access(path_access, F_OK) == 0)
		{
			if (access(path_access, X_OK) == 0)
			{
				return (path_access);
			}
			perror(path_access);
			data->sortie = errno;
			return (NULL);
		}
		free(path_access);
		i++;
	}
	data->sortie = 127;
	command_not_found(command->command);
	return (NULL);
}

char	*command_path(t_command *command, t_data *data)
{
	char	**paths;
	char	*path_access;

	if (strchr(command->command, '/'))
	{
		if (access(command->command, F_OK | X_OK) == 0)
		{
			if (!check_dir(command->command, command->command, data))
				return (command->command);
		}
		else
		{
			perror(command->command);
			data->sortie = errno;
		}
		free(command->command);
		return (NULL);
	}
	paths = split_path(data);
	if (!paths)
		return (NULL);
	path_access = command_path_utils(command, data, paths);
	free_arg(paths);
	free(command->command);
	return (path_access);
}
