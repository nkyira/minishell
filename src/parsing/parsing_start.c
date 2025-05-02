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

static int	uniq_space(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (!ft_isspace(input[i]))
			return (0);
		i++;
	}
	return (1);
}

int	parsing_start(t_data *data)
{
	if (uniq_space(data->input))
		return (0);
	if (quote_error(data->input))
	{
		data->sortie = 2;
		return (0);
	}
	if (separator(data, data->input, DEFAULT) == -1)
		return (0);
	if (!check_tokens(data->token))
	{
		data->sortie = 2;
		return (0);
	}
	if (replace(data))
		return (0);
	//check_token_again(&data->token);
	if (!create_commands(&data->command, data->token))
		return (0);
	execute(data);
	return (1);
}
