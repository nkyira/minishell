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

int	posix_error(int c)
{
	if (c == 2)
		return (127);
	if (c == 13)
		return (126);
	if (c == 4)
		return (130);
	if (c == 12)
		return (12);
	if (c == 17)
		return (17);
	return (c);
}

int	check_dir(char *path, char *cmd, t_data *data)
{
	struct stat	path_stat;

	stat(path, &path_stat);
	if (!S_ISREG(path_stat.st_mode))
	{
		data->sortie = 126;
		write(2, cmd, ft_strlen(cmd));
		ft_putendl_fd(" : Is a directory", 2);
		return (1);
	}
	return (0);
}

void	command_not_found(char *command)
{
	write(2, "minishell: ", 11);
	write(2, command, ft_strlen(command));
	ft_putendl_fd(" : command not found", 2);
}

void	error_tube(void)
{
	ft_putendl_fd("probleme survenu lors de la creation du pipe\n", 2);
}

void	heredoc_warning(char *str)
{
	write(2, "warning: here-document delimited by end-of-file (wanted '", 57);
	write(2, str, ft_strlen(str));
	ft_putendl_fd("')", 2);
}
