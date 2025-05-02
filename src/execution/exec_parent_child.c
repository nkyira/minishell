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

int	get_children(t_data *data, pid_t pid)
{
	pid_t	wpid;
	int		status;
	int		save_status;

	save_status = 0;
	wpid = 0;
	while (wpid != -1 || errno != ECHILD)
	{
		wpid = waitpid(-1, &status, 0);
		//printf("%d --- %d---status %d\n",wpid,pid,status);
		if (wpid == pid)
			save_status = status;
		continue ;
	}
	if (WIFSIGNALED(save_status))
		status = 128 + WTERMSIG(save_status);
	else if (WIFEXITED(save_status))
		status = WEXITSTATUS(save_status);
	else
		status = save_status;
	data->sortie = posix_error(status);
	return (data->sortie);
}

void	parent_process(int *prev_fd, t_data *data, t_command *cmd)
{
	if (cmd->prev)
		close(*prev_fd);
	if (cmd->next)
		*prev_fd = data->pipefd[0];
	close(data->pipefd[1]);
}

void	child_process(t_command *command, t_data *data, int prev_fd)
{
	int	sortie;
	int	entree;

	sortie = 0;
	entree = 0;
	if (command->next)
		sortie = dup2(data->pipefd[1], STDOUT_FILENO);
	if (command->prev)
		entree = dup2(prev_fd, STDIN_FILENO);
	close(data->pipefd[1]);
	close(data->pipefd[0]);
	if (command->prev)
		close(prev_fd);
	if (sortie != -1 && entree != -1)
		execute_commande(data, command);
	ft_exit(data, data->sortie);
}
