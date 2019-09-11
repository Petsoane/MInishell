/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpetsoan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 14:44:16 by lpetsoan          #+#    #+#             */
/*   Updated: 2019/09/11 11:16:41 by lpetsoan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	parse_env_var(char **env, char **i_split);

void	sigint(int i)
{
	ft_putstr("\b\b\b\b    \n");
	ft_putstr(PROMPT);
}

/*
** This Function will handle all the input processsing.
** Migt also handle the autocomplete, history, and other fuctionalities.
*/

char	**get_input(char **env)
{
	char *input;
	char **i_split;
	/* int ret; */

	signal(SIGINT, sigint);

	/* ret = get_next_line(1, &input); */
	ft_putstr(PROMPT);
	while (ft_strcmp((input = readline("\b\b$>")), "") == 0)
	{
		ft_putstr(PROMPT);
		free(input);
	}
	add_history(input);
	i_split = ft_strsplit(input, ' ');
	parse_env_var(env, i_split);
	free(input);
	return (i_split);
}

void	parse_env_var(char **env, char **input_split)
{
	int i;
	char *env_var;
	char *tmp;

	i = 0;
	while (input_split[i] != NULL)
	{
		if (input_split[i][0] == '$')
		{
			tmp = input_split[i];
			env_var = env_var_value(env, tmp + 1);
			input_split[i] = env_var != NULL ? env_var : ft_strdup("abcd");
			free(tmp);
		}
		i++;
	}
}
