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

static int	check_word(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[0]) && str[0] != '_')
	{
		return (-1);
	}
	while (str[i])
	{
		if (special_character(str[i]))
			return (-1);
		i++;
	}
	return (0);
}

void	delete_env_var(char **env, int d)
{
	int	i;

	if (d == -1)
		return ;
	while (env[i])
	{
		if (i == d)
		{
			free(env[i]);
			break ;
		}
		i++;
	}
	while (env[i])
	{
		env[i] = env[i + 1];
		i++;
	}
}

void	unset_builtin(t_data *data, char **argv)
{
	int	i;
	int	d;

	i = 1;
	while (argv[i])
	{
		if (check_word(argv[i]) == -1)
		{
			error_export(argv[i]);
			data->sortie = 1;
		}
		else
		{
			d = position_env(argv[i], data->env, ft_strlen(argv[i]));
			delete_env_var(data->env, d);
			d = position_env(argv[i], data->export, ft_strlen(argv[i]));
			delete_env_var(data->export, d);
		}
		i++;
	}
}
