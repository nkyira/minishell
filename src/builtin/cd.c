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

static void cd_error(char *str)
{
	write(2, "cd: ", 4);
	write(2, str, ft_strlen(str));
	ft_putendl_fd(": No such file or directory",2);
}

static int	cd_access_error(char *str)
{
	if (str[0] == '-')
	{
		write(2, "cd: ", 4);
		write(2, str, ft_strlen(str));
		ft_putendl_fd(": invalid option", 2);
		return (1);
	}
	if (access(str, F_OK) != 0)
	{
		perror(str);
		return (1);
	}
	return (0);
}

int cd_builtin(char **argv)
{	
	struct stat	path_stat;

	if (argv[1])
	{
		if (argv[2])
		{
			ft_putendl_fd("cd: too many arguments", 2);
			return (1);
		}
		if (cd_access_error(argv[1]))
			return (1);
		stat(argv[1], &path_stat);
		if (S_ISREG(path_stat.st_mode))
		{
			cd_error(argv[1]);
			return (1);
		}
		if (chdir(argv[1]) != 0)
		{
			perror(argv[1]);
			return (1);
		}
	}
	return (0);
}
