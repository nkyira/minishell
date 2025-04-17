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

int check_word(char *str)
{
	int	i;

	i = 0;	
	if (!ft_isalpha(str[0]) && str[0] != '_')
	{
		return (-1);
	}
	while (str[i] && str[i] != '=')
	{
		if (special_character(str[i]))
			return (-1);
		i++;
	}
	if (str[i] != '=')
		return (0);
	return (1);
}

void	error_export(char *str)
{
	write(2, "export: `", 9);
	write(2, str, ft_strlen(str));
	ft_putendl_fd("': not a valid identifier", 2);
}

int	export(t_data *data, char *str)
{
	int		erreur;
	int		pos;
	
	erreur = 0;
	pos = position_env(str, data, env_parcourt(str));
	if (pos != -1)
	{
		data->env[pos] = change_var_env(str, data->env[pos]);
		return (1);
	}
	data->env = ft_new_env(data->env, str, &erreur);
	if (erreur)
	{
		perror("Error");
		return (-1);
	}
	return (1);
}

void	export_builtin(t_data *data, char **argv)
{
	int	i;
	int	verifi;

	i = 1;
	(void)data;
	while (argv[i])
	{
		verifi = check_word(argv[i]);
		if (verifi == -1)
		{
			error_export(argv[i]);
			data->sortie = 1;
		}
		else if (verifi == 1)
		{
			if (export(data, argv[i]) == -1)
				return ;
		}
		i++;
	}
}