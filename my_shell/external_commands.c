/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpetsoan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 19:56:13 by lpetsoan          #+#    #+#             */
/*   Updated: 2019/09/11 13:12:08 by lpetsoan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	sigmain(int i)
{
	ft_putstr("int the external:");
	ft_putstr("\n");
}

void	run_bin(char **argv, char **env)
{
	char *bin_path;
	int pid;

	// Check to see if the function exist in the binary list
	if ((bin_path = get_bin_path(env_var_value(env, "PATH"), *argv)) != NULL)
	{
		// If found, fork a process and execute it.
		signal(SIGINT, sigmain);
		pid = fork();
		if (pid == 0)
		{
			execve(bin_path, argv, env);
			free(bin_path);
			return ;
		}
		wait(NULL);
		free(bin_path);
	}
	else
	{
		print_form("lsh: command does not exist : %s\n", *argv);
	}
}

char	*get_bin_path(char *path_var, char *bin_name)
{
	char *out;
	char *tmp;
	char **bin_paths;

	bin_paths = ft_strsplit(path_var, ':');
	while (*bin_paths != NULL)
	{
		out = ft_strdup(*bin_paths);
		tmp = out;
		out = ft_strjoin(out, "/");
		free(tmp);

		tmp = out;
		out = ft_strjoin(out, bin_name);
		free(tmp);
		if (access(out, F_OK) == 0)
		{
			while (*bin_paths != NULL)
				free(*bin_paths++);
			free(path_var);
			return (out);
		}
		free(out);
		free(*bin_paths);
		bin_paths++;
	}
	free(path_var);
	return (NULL);
}

