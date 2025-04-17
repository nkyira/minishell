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

void	lecture(t_token *token)
{
	int i;

	i = 0;
	while (token)
	{
		printf("%d-%s type == %d\n",token->index, token->str, token->type);
		token = token->next;
		i++;
	}
}

void lecture_command(t_data data)
{
	int i = 0;

	t_command	*command = data.command;
	t_redict	*outfile = command->outfile;
	t_redict	*inputfile = command->inputfile;
	while (command)
	{
		printf("%s ", command->command);
		while (outfile)
		{
			printf("outfile %s ", outfile->file);
			outfile = outfile->next;
		}
		while (inputfile)
		{
			printf("infile %s ", inputfile->file);
			inputfile = inputfile->next;
		}
		while (command->args && command->args[i])
		{
			printf("word %s ",command->args[i]);
			i++;
		}
		printf("\n");
		command = command->next;
		i = 0;
		if(!command)
			break;
		outfile = command->outfile;
		inputfile = command->inputfile;
	}
}

int main(int argc, char **argv, char **env)
{
	char *r;
	int i = 0;
	t_data data;
	
	(void)argc;
	(void)argv;
	data.sortie = 0;
	data.env = copy_env(env);
	if (!data.env)
		return (1);
	init_data(&data, NULL);
	while (1)
	{
		signals_interactif();
		r = readline("prompt >");
		init_data(&data, r);
		if (!r)
			exit_builtin(&data, NULL);
		add_history(r);
		signals_noninteractif();
		if (parsing_start(&data))
		{
			//lecture_command(data);
			;
		}
		else
		{
		}
		free_data(&data);
		i++;
	}
	ft_exit(&data, 1);
	return (0);
}
