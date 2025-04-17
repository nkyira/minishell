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

int	is_number(char *tab)
{
	int	i;
	int	space;

	i = 0;
	space = 0;
	while (tab[i] && ft_isspace(tab[i]))
		i++;
	if (!tab[i])
		return (0);
	if ((tab[i] == '-' || tab[i] == '+') && tab[i + 1] < 48 && tab[i + 1] > 57)
		return (0);
	if (tab[i] == '-' || tab[i] == '+')
		i++;
	while (tab[i])
	{
		if (ft_isspace(tab[i]))
			space = 1;
		else if (tab[i] < 48 || tab[i] > 57)
			return (0);
		else if (tab[i] >= 48 && tab[i] <= 57 && space)
			return (0);
		i++;
	}
	return (1);
}

void	exit_builtin(t_data *data, char **argv)
{
	printf("exit\n");
	if (!argv || !argv[0])
		ft_exit(data, data->sortie);
	else if (argv[1])
	{
		if (!is_number(argv[1]))
		{
			write(2, "bash: exit: ", 12);
			write(2, argv[1], ft_strlen(argv[1]));
			ft_putendl_fd(": numeric argument required", 2);
			ft_exit(data, STDERR_FILENO);
		}
		if (argv[2])
		{
			ft_putendl_fd("bash: exit: too many arguments", 2);
			data->sortie = 1;
			return ;
		}
		ft_exit(data, ft_atoi(argv[1]));
	}
	ft_exit(data, data->sortie);
}
