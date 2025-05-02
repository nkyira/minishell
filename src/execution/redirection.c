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

int redirect_infile(int fd)
{
	if (fd == -1)
		return (-1);
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		ft_putendl_fd(strerror(errno), 2);
		close(fd);
		if (access("heredoc.tmp", F_OK) == 0)
			unlink("heredoc.tmp");
		return (-1);
	}
	close(fd);
	if (access("heredoc.tmp", F_OK) == 0)
		unlink("heredoc.tmp");
	return (0);
}

int	append(int fd)
{
	if (fd == -1)
		return (-1);
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		ft_putendl_fd(strerror(errno), 2);
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}
