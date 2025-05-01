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

static char	*world_env(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=' && str[i])
		i++;
	return (str + i + 1);
}

int	env_parcourt(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (i);
}

int	position_env(char *str, char **env, int n)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (n != env_parcourt(env[i]))
		{
			i++;
			continue ;
		}
		if (ft_strncmp(str, env[i], n) == 0)
		{
			return (i);
		}
		i++;
	}
	return (-1);	
}

char	*search_env(char *str, t_data *data, int n)
{
	int	i;

	i = 0;
	if (str[0] == '?')
	{
		return (ft_itoa(data->sortie));
	}
	while (data->env[i])
	{
		if (n != env_parcourt(data->env[i]))
		{
			i++;
			continue ;
		}
		if (ft_strncmp(str, data->env[i], n) == 0)
		{
			return (world_env(data->env[i]));
		}
		i++;
	}
	return (NULL);
}
