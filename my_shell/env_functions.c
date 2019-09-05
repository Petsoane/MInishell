/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpetsoan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 07:08:54 by lpetsoan          #+#    #+#             */
/*   Updated: 2019/09/04 12:34:14 by lpetsoan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int env_var_pos(char **env, char *var_name)
{
	int pos;

	pos = 0;
	while (env[pos] != NULL)
	{
		if (ft_strncmp(env[pos], var_name, ft_strlen(var_name)) == 0)
			return (pos);
		pos++;
	}
	return (-1);
}

char	*env_var_value(char **env, char *var_name)
{
	char *out;
	int ac;

	ac = 32;
	out = ft_strdup(env[env_var_pos(env, var_name)] + ft_strlen(var_name) + 1);
	return (out);
}

void	set_env_var(char **env, char *var_name, char *val)
{
	int pos;
	char *new_env_var;
	char *tmp;

	new_env_var = ft_strdup(var_name);
	tmp = new_env_var;
	new_env_var = ft_strjoin(tmp, "=");
	free(tmp);

	tmp = new_env_var;
	new_env_var = ft_strjoin(tmp, val);
	free(tmp);
	pos = env_var_pos(env, var_name);
	if (pos != -1)
	{
		tmp = env[pos];
		env[pos] = new_env_var;
		free(tmp);
	}
}
