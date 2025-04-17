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

static int	redirect_heredoc(char *str)
{
	char	*r;
	int		fd;

	fd = open("heredoc.tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putendl_fd(strerror(errno), 2);
		return (-1);
	}
	while (1)
	{
		signals_interactif();
		r = readline(">");
		signals_noninteractif();
		if (!r || ft_strncmp(r, str, ft_strlen(str)) == 0)
		{
			if (!r)
				heredoc_warning(str);
			break ;
		}
		ft_putendl_fd(r, fd);
		free(r);
	}
	close(fd);
	return (0);
}

static int	heredoc(t_redict *redirection)
{
	t_redict	*temp;

	temp = redirection;
	while (temp)
	{
		if (temp->type == HEREDOC)
		{
			if (redirect_heredoc(temp->file) == -1)
				return (-1);
		}
		temp = temp->next;
	}
	return (1);
}

static void	error_file(t_redict *temp)
{
	if (temp->type == HEREDOC)
		perror("heredoc.tmp");
	else
		perror(temp->file);
}

static int	input_course(t_redict *temp)
{
	int	fd;

	while (temp)
	{
		if (temp->type == HEREDOC)
			fd = open("heredoc.tmp", O_RDONLY);
		else
			fd = open(temp->file, O_RDONLY);
		if (fd == -1)
		{
			error_file(temp);
			return (-1);
		}
		if (dup2(fd, STDIN_FILENO) == -1)
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

int	redirect_input(t_redict *redirection)
{
	t_redict	*temp;

	temp = redirection;
	if (heredoc(redirection) == -1)
		return (-1);
	if (input_course(temp) == -1)
		return (-1);
	if (access("heredoc.tmp", F_OK) == 0)
		unlink("heredoc.tmp");
	return (0);
}
