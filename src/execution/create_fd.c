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
		if (!r || ft_strncmp(r, str, ft_max(ft_strlen(str), ft_strlen(r))) == 0)
		{
			if (!r)
				heredoc_warning(str);
			break ;
		}
		ft_putendl_fd(r, fd);
		free(r);
	}
	if (r)
		free(r);
	close(fd);
	return (0);
}

int infile(t_token *token)
{
	int fd;

	if (token->type == HEREDOC)
	{
		redirect_heredoc(token->next->str);
		fd = open("heredoc.tmp", O_RDONLY);
	}
	else
		fd = open(token->next->str, O_RDONLY);
	if (token->type == HEREDOC && fd == -1)
		perror("heredoc.tmp");
	else if (fd == -1)
		perror(token->next->str);
	return (fd);
}

int outfile(t_token *token)
{
	int fd;

	if (token->type == TRUNC)
		fd = open(token->next->str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		fd = open(token->next->str, O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (fd == -1)
		perror(token->next->str);
	return (fd);
}