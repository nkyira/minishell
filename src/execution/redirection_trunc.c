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

int	append(t_redict *redirection)
{
	t_redict	*temp;
	int			fd;

	temp = redirection;
	while (temp)
	{
		if (temp->type == TRUNC)
			fd = open(temp->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else
			fd = open(temp->file, O_CREAT | O_APPEND | O_WRONLY, 0644);
		if (fd == -1)
		{
			perror(temp->file);
			return (-1);
		}
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			ft_putendl_fd(strerror(errno), 2);
			close(fd);
			return (-1);
		}
		close(fd);
		temp = temp->next;
	}
	return (0);
}
