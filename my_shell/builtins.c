/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpetsoan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 10:31:40 by lpetsoan          #+#    #+#             */
/*   Updated: 2019/09/11 17:58:33 by lpetsoan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		parse_command(char **av, char **env)
{
	static char *commands[COMMANDS];
	static functions exec[FUNCTIONS];
	int i;

	i = 0;
	if (env_var_pos(env, BUILTS) == -1)
	{
		prep_commands(commands);
		builtin_functions(exec);
		add_var_builtins(env, commands);
	}
	// Argument count can be put here.
	while (i < FUNCTIONS)
	{
		if (ft_strcmp(av[0], commands[i]) == 0)
			break;
		i++;
	}
	if (commands[i] == NULL)
	{
		return (-1);
	}
	else
		exec[i](env, av + 1);
	return (0);
}

void	add_var_builtins(char **env, char **commands)
{
	int i;
	char *path;
	char *tmp;

	path = ft_strdup(commands[0]);
	i = 1;
	while (commands[i] != NULL)
	{
		tmp = path;
		path = ft_strjoin(tmp, ":");
		free(tmp);
		tmp = path;
		path = ft_strjoin(tmp, commands[i]);
		free(tmp);
		i++;
	}
	set_env_var(env, BUILTS, path);
	free(path);
}
void	prep_commands(char **av)
{
	av[0] = "echo";
	av[1] = "cd";
	av[2] = "pwd";
	av[3] = "env";
	av[4] = "unset";
	av[5] = "which";
	av[6] = NULL;
}

void	builtin_functions(functions *exec)
{
	exec[0] = &echo; 
	exec[1] = &cd;
	exec[2] = &pwd;
	exec[3] = &environment;
	exec[4] = &unset_env_var;
	exec[5] = &which;
}

void	which(char **env, char **av)
{
	int ac;
	int i;
	char *path;
	char *var_value;
	char **split;

	ac = env_var_count(av);
	if (ac != 0)
	{
		i = 0;
		var_value = env_var_value(env, BUILTS);
		split = ft_strsplit(var_value, ':');
		while (i != ac)
		{
			if (is_builtins(env, av[i], split) == 1)
				print_form("%s: shell builtin command\n");
			else if ((path = get_bin_path(env_var_value(env, "PATH"), av[i])) != NULL)
			{
				ft_putendl(path);
				free(path);
			}
			i++;
		}
		while (*split != NULL)
			free(*split++);
		free(var_value);
	}
}

int		is_builtins(char **env, char *command, char **split)
{
	while (*split != NULL)
	{
		if (ft_strcmp(*split, command) == 0)
			return (1);
		split++;
	}
	return (0);
}

void	cd(char **env, char **av)
{
	// This is where the argument count could be put.
	int i;
	char *path;
	char *pwd;
	char cwd[255];

	i = 0;
	while (av[i] != NULL)
		i++;
	if (i == 0 || ft_strcmp(av[0], "~") == 0)
	{
		path = env_var_value(env, "HOME");
		// the error displaying can be put into function all on its own.
		if (chdir(path) == -1)
			ft_putendl("pwd: no such file direcotory exists.");
		free(path);
	}
	else if (chdir(av[0]) == -1)
		ft_putendl("pwd : no such file or directory");
	pwd = env_var_value(env, "PWD");
	set_env_var(env, "OLDPWD", pwd);
	getcwd(cwd, sizeof(cwd));
	set_env_var(env, "PWD", cwd);
	free(pwd);
}

void	echo(char **env, char **av)
{
	while (*av != NULL)
	{
		ft_putstr(*av);
		ft_putstr(" ");
		av++;
	}
	puts("");
}

void	pwd(char **env, char **av)
{
	char cwd[255];
	// This is where the argument count loop or function might go.
	if (getcwd(cwd,sizeof(cwd)) == NULL)
		ft_putendl("Error printing the directory");
	ft_putendl(cwd);
}
