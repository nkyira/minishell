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

void	exe_one_built(t_data *data, t_command *command, int *stdi, int *stdo)
{
	if (command->inputfile)
	{
		if (redirect_infile(command->infile) == -1)
		{
			data->sortie = 1;
			return ;
		}
	}
	if (command->outfile)
	{
		if (append(command->ofile))
		{
			data->sortie = 1;
			return ;
		}
	}
	if (ft_strncmp(command->command, "exit", 4) == 0)
		close_fds_one_builtin(command, stdo, stdi);
	execute_builtin(data, command);
}

void	execute_execve(t_data *data, char **args, t_command *command)
{
	int		pos;
	int		shlvl;
	char	*temp;
	char	*str;

	if (!ft_memcmp(args[0], MINISHELL, ft_max(ft_strlen(MINISHELL),\
		 ft_strlen(args[0]))))
	{
		pos = position_env(SHELLEVEL,data->env,ft_strlen(SHELLEVEL));
		shlvl = ft_atoi(data->env[pos] + env_parcourt(data->env[pos]) + 1) + 1;
		temp = ft_itoa(shlvl);
		if (!temp)
			return ;
		str = ft_strjoin("SHLVL=", temp);
		free(temp);
		if (!str)
			return ;
		if (export(&data->env, str) == -1 || export(&data->export, str) == -1)
		{
			free(str);
			return ;
		}
		free(str);
	}
	execve(command->command, args, data->env);
}

void	execute_commande(t_data *data, t_command *command)
{
	int	builtin;

	builtin = is_builtin(command->command);
	if (command->infile != -2)
	{
		if (redirect_infile(command->infile) == -1)
		{
			data->sortie = 1;
			return ;
		}
	}
	if (command->ofile != -2)
	{
		if (append(command->ofile))
		{
			data->sortie = 1;
			return ;
		}
	}
	if (!builtin && command->command)
		command->command = command_path(command, data);
	if (!builtin && command->command)
		execute_execve(data, command->args, command);
	else if (command->command)
		execute_builtin(data, command);
}
