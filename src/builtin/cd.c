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

static void	cd_error(char *str)
{
	write(2, "cd: ", 4);
	write(2, str, ft_strlen(str));
	ft_putendl_fd(": No such file or directory", 2);
}

static int	cd_access_error(t_data *data, char *str)
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
		data->sortie = 1;
		perror(str);
		return (1);
	}
	return (0);
}

static int	raccourci(t_data *data, char *str)
{
	char	*temp;

	if (!ft_memcmp(str, "-", ft_strlen(str)))
	{
		if (!data->oldpwd)
			return (1);
		printf("%s\n", data->oldpwd);
		temp = ft_strdup(data->oldpwd);
		if (!temp)
			return (1);
		getcwd(data->oldpwd, sizeof(data->oldpwd));
		if (chdir(temp) != 0)
		{
			perror(str);
			free(temp);
			data->sortie = 1;
			return (1);
		}
		free(temp);
		return (1);
	}
	return (0);
}

static int	check_road(t_data *data, char *str)
{
	struct stat	path_stat;

	if (raccourci(data, str))
		return (1);
	if (cd_access_error(data, str))
		return (1);
	stat(str, &path_stat);
	if (S_ISREG(path_stat.st_mode))
	{
		cd_error(str);
		data->sortie = 1;
		return (1);
	}
	return (0);
}

void	cd_builtin(t_data *data, char **argv)
{	
	if (argv[1])
	{
		if (argv[2])
		{
			ft_putendl_fd("cd: too many arguments", 2);
			data->sortie = 1;
			return ;
		}
		if (check_road(data, argv[1]))
			return ;
		getcwd(data->oldpwd, sizeof(data->oldpwd));
		if (chdir(argv[1]) != 0 || !data->oldpwd)
		{
			perror(argv[1]);
			data->sortie = 1;
			return ;
		}
	}
}
