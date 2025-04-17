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

int size_list_char(char **argv)
{
	int	i;

	i = 0;
	while(argv[i])
		i++;
	return (i);
}

char	**copy_env(char **env)
{
	char	**new_env;
	int		i;

	i = 0;
	new_env = malloc(sizeof(char *) * (size_list_char(env) + 1));
	if (!new_env)
	{
		perror("Error");
		return (NULL);
	}
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
		{
			perror(new_env[i]);
			free_arg(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

char	**ft_new_env(char **env, char *str, int *error)
{
	char	**new_env;
	int		i;

	i = 0;
	new_env = malloc(sizeof(char *) * (size_list_char(env) + 2));
	if (!new_env)
	{
		*error = 1;
		return (env);
	}
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
		{
			free_arg(new_env);
			*error = 1;
			return (env);
		}
		i++;
	}
	new_env[i] = ft_strdup(str);
	new_env[i + 1] = NULL;
	free_arg(env);
	return (new_env);
}

char	*change_var_env(char *str, char *var_env)
{
	char	*new_str;

	new_str = ft_strdup(str);
	if (!new_str)
	{
		perror(new_str);
		return (var_env);
	}
	free(var_env);
	return (new_str);
}
