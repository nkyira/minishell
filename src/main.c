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

#include "../include/minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*r;
	t_data	data;

	(void)argc;
	(void)argv;
	data.sortie = 0;
	data.env = copy_env(env);
	data.export = copy_env(env);
	if (!getcwd(data.oldpwd, sizeof(data.oldpwd)) || !data.env || !data.export)
		return (1);
	while (1)
	{
		signals_interactif();
		r = readline("prompt >");
		init_data(&data, r);
		if (!r)
			exit_builtin(&data, NULL);
		add_history(r);
		signals_noninteractif();
		parsing_start(&data);
		free_data(&data);
	}
	ft_exit(&data, 1);
	return (0);
}
