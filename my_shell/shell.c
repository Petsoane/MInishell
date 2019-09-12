/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpetsoan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 08:14:07 by lpetsoan          #+#    #+#             */
/*   Updated: 2019/09/11 17:58:32 by lpetsoan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	**prep_env_vec(char **sys_vec);


// i need to change the structure of my program to better traverse the input
// vector.
int main(int ac, char **av, char **sys_env)
{
	char **input_split;
	char **env;
	int count;
	int i;

	// try moving the prep of builtin commands and functions here
	// so as to run them once.

	env = prep_env_vec(sys_env);
	while (1)
	{
		input_split = get_input(env);
		if (ft_strcmp(*input_split, "exit") == 0)
			break;
		while (*input_split != NULL && valid_env_var(*input_split) == 1)
		{
			set_env(env, *input_split);
			free(*input_split);
			input_split++;
		}
		if (*input_split == NULL)
			continue;
		if (parse_command(input_split, env) == -1)
		{
			// If there is no builtin command matchin this command string.
			// simply try to find the matchin binary and execute it.
			run_bin(input_split, env);
		}
		while (*input_split != NULL)
			free(*input_split++);
	}
	// freeing the environment var vector.
	count = env_var_count(sys_env);
	i = 0;
	while (i < (count * 2))
	{
		free(env[i]);
		i++;
	}
	getchar();
}

char	**prep_env_vec(char **sys_vec)
{
	char **env;
	int i;

	i = env_var_count(sys_vec);
	env = (char **)malloc(sizeof(char *) * (i * 2));
	i = 0;
	while (sys_vec[i] != NULL)
	{
		env[i] = ft_strdup(sys_vec[i]);
		i++;
	}
	env[i] = NULL;
	return (env);
}
