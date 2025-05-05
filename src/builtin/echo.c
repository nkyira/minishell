/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                              :+:    :+:           */
/*                                                    +:+ +:+         +:+     */
/*   By: fatsaa-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:46:24 by fatsaa-m          #+#    #+#             */
/*   Updated: 2025/05/02 17:24:11 by jodavis        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	successive_n(char *str)
{
	int	i;

	i = 2;
	if (str[1] != 'n')
	{
		return (0);
	}
	while (str[i] == 'n')
	{
		i++;
	}
	if (str[i] != '\0')
		return (0);
	return (1);
}

int	echo_builtin(char **argv)
{
	int	i;
	int	no_new_line_flag;

	i = 1;
	no_new_line_flag = 0;
	while (argv[i] && argv[i][0] == '-' && successive_n(argv[i]))
	{
		no_new_line_flag = 1;
		i++;
	}
	while (argv[i])
	{
		ft_printf("%s", argv[i]);
		if (argv[i + 1] != NULL)
			ft_printf(" ");
		i++;
	}
	if (no_new_line_flag == 0)
		ft_printf("\n");
	return (0);
}
