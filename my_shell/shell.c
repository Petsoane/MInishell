/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpetsoan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 08:14:07 by lpetsoan          #+#    #+#             */
/*   Updated: 2019/09/04 12:34:08 by lpetsoan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "shell.h"

char	**prep_env_vec(char **sys_vec);

int main(int ac, char **av, char **sys_env)
{
	char *out;
	char **input_split;
	int ret;
	char **env;

	// try moving the prep of builtin commands and functions here
	// so as to run them once.
	env = prep_env_vec(sys_env);
	ret = 0;
	while (env[ret] != NULL)
	{
		ft_putendl(env[ret]);
		ret++;
	}
	while (1)
	{
		ft_putstr(PROMPT);		// this value can be put into a PSI macro.
		ret = get_next_line(1, &out);
		if (ft_strcmp(out, "exit") == 0)
			break;
		input_split = ft_strsplit(out, ' ');
		if (*input_split == NULL)
			continue;
		if (parse_command(input_split, env) == -1)
		{
			ft_putendl("Error");
		}
		while (*input_split != NULL)
			free(*input_split++);
	}
	int i = 0;
	while(env[i] != NULL)
	{
		ft_putendl(env[i]);
		free(env[i++]);
	}
}

char	**prep_env_vec(char **sys_vec)
{
	char **env;
	int i;

	i = 0;
	while (sys_vec[i] != NULL)
	{
		i++;
	}
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
