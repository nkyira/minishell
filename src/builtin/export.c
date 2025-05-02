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

int	check_word(char *str)
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
	if (str[i] == '=' && str[i + 1])
		return (1);
	return (0);
}

void	error_export(char *str)
{
	write(2, "export: `", 9);
	write(2, str, ft_strlen(str));
	ft_putendl_fd("': not a valid identifier", 2);
}

int	export(char ***env, char *str)
{
	int		erreur;
	int		pos;

	erreur = 0;
	pos = position_env(str, *env, env_parcourt(str));
	if (pos != -1)
	{
		(*env)[pos] = change_var_env(str, (*env)[pos]);
		return (1);
	}
	*env = ft_new_env(*env, str, &erreur);
	if (erreur)
	{
		perror("Error");
		return (-1);
	}
	return (1);
}

void	loop(t_data *data, char **argv)
{
	int	i;
	int	verifi;

	i = 0;
	while (argv[++i])
	{
		verifi = check_word(argv[i]);
		if (verifi == -1)
		{
			error_export(argv[i]);
			data->sortie = 1;
		}
		if (verifi == 0)
		{
			if (export(&data->export, argv[i]) == -1)
				return ;
		}
		if (verifi == 1)
		{
			if (export(&data->export, argv[i]) == -1)
				return ;
			if (export(&data->env, argv[i]) == -1)
				return ;
		}
	}
}

void	export_builtin(t_data *data, char **argv)
{
	int	i;

	i = -1;
	if (!argv[1])
	{
		while (data->export[++i])
		{
			ft_putstr_fd("export ", 1);
			ft_putendl_fd(data->export[i], 1);
		}
	}
	loop(data, argv);
}
