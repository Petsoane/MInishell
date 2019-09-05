/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpetsoan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 07:08:54 by lpetsoan          #+#    #+#             */
/*   Updated: 2019/09/05 14:29:50 by lpetsoan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** This function gets the position an environment variable.
*/

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

/*
** This function gets the environment variable value.
*/

char	*env_var_value(char **env, char *var_name)
{
	char *out;
	int ac;

	ac = 32;
	out = ft_strdup(env[env_var_pos(env, var_name)] + ft_strlen(var_name) + 1);
	return (out);
}

/*
** This fucntion will change environment variable or add a new one
*/

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
	else
	{
		int env_c;
		env_c = env_var_count(env);
		env[env_c] = new_env_var;
		env[env_c + 1] = NULL;
	}
}

/*
** This function count the number of varibles in the environment.
*/

int		env_var_count(char **env)
{
	int ac; 

	ac = 0;
	while (env[ac] != NULL)
		ac++;
	return (ac);
}

/*
** This function prints the environment variables on the screen
*/

void	print_env(char **env)
{
	while (*env != NULL)
	{
		ft_putendl(*env++);
	}
}

/*
** This is the builtin function for 'env'.
** it is still not complete.
*/

void	environment(char **env, char **av)
{
	int ac;

	ac = 0;
	while (av[ac] != NULL)
		ac++;
	if (ac == 0)
		print_env(env);
}

int		valid_env_var(char *new_var)
{
	int valid_form;

	valid_form = -1;
	while (*new_var)
	{
		if (*new_var == ' ')
			return (-1);
		if (*new_var == '=')
			valid_form = 1;
		new_var++;
	}
	return (valid_form); 
}

void	set_env(char **env, char *new_var)
{
	int i;
	char *var_name;
	char *var_val;

	i = 0;
	while (new_var[i] != '=')
		i++;
	var_name = ft_strndup(new_var, i);
	var_val = ft_strdup(new_var + (i + 1));
	set_env_var(env, var_name, var_val);
}

void	unset_env_var(char **env, char **av)
{
	int pos;
	int prev;
	char *tmp;

	while (*av != NULL)
	{
		pos = env_var_pos(env, *av);
		if (pos != -1)
		{
			tmp = env[pos];
			prev = pos;
			pos++;
			while (env[pos] != NULL)
			{
				env[prev] = env[pos];
				prev = pos;
				pos++;
			}
			env[prev] = env[pos];
			free(tmp);
		}
		av++;
	}
}
