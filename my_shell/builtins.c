/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpetsoan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 10:31:40 by lpetsoan          #+#    #+#             */
/*   Updated: 2019/09/04 12:34:10 by lpetsoan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		parse_command(char **av, char **env)
{
	char *commands[COMMANDS];
	functions exec[FUNCTIONS];
	int i;

	i = 0;
	prep_commands(commands);
	builtin_functions(exec);
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
		exec[i](av + 1, env);
	return (0);
}

void	prep_commands(char **av)
{
	av[0] = "echo";
	av[1] = "cd";
	av[2] = "pwd";
	av[3] = NULL;
}

void	builtin_functions(functions *exec)
{
	exec[0] = &echo; 
	exec[1] = &cd;
	exec[2] = &pwd;
}

void	cd(char **av, char **env)
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

void	echo(char **av, char **env)
{
	while (*av != NULL)
	{
		ft_putstr(*av);
		ft_putstr(" ");
		av++;
	}
	puts("");
}

void	pwd(char **av, char **env)
{
	char cwd[255];
	// This is where the argument count loop or function might go.
	if (getcwd(cwd,sizeof(cwd)) == NULL)
		ft_putendl("Error printing the directory");
	ft_putendl(cwd);
}
