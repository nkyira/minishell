#include "../../include/minishell.h"

void	env_builtin(t_data *data, char **argv)
{
	int i;

	i = 0;
	(void)argv;
	if (!data || !data->env)
	{
		return ;
	}
	while (data->env[i])
	{
		printf("%s\n",data->env[i]);
		i++;
	}
}