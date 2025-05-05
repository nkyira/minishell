/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   env.c                                               :+:    :+:           */
/*                                                      +:+                   */
/*   By: jodavis <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/05/02 17:25:07 by jodavis        #+#    #+#                */
/*   Updated: 2025/05/02 17:25:14 by jodavis        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	env_builtin(t_data *data, char **argv)
{
	int	i;

	i = 0;
	data->sortie = 0;
	(void)argv;
	if (!data || !data->env)
	{
		return ;
	}
	while (data->env[i])
	{
		printf("%s\n", data->env[i]);
		i++;
	}
}
