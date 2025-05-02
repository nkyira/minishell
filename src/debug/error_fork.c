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

void	error_fork(t_data *data)
{
	close(data->pipefd[1]);
	close(data->pipefd[0]);
	error_tube();
}

void	no_such_file(char *command)
{
	write(2, "minishell: ", 11);
	write(2, command, ft_strlen(command));
	ft_putendl_fd(" : No such file or directory", 2);
}
