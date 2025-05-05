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

void	pwd_builtin(t_data *data, char **argv)
{
	char	buf[PATH_MAX];

	(void)argv;
	data->sortie = 0;
	if (getcwd(buf, sizeof(buf)))
	{
		ft_putendl_fd(buf, 1);
	}
	else
	{
		ft_putendl_fd(strerror(errno), 2);
		data->sortie = errno;
		return ;
	}
}
