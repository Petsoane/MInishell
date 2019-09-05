/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpetsoan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 08:27:18 by lpetsoan          #+#    #+#             */
/*   Updated: 2019/09/04 12:34:22 by lpetsoan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft/libft.h"

typedef void (*functions)();
void	echo(char **av, char **env);
void	cd(char **av, char **env);
void	pwd(char **av, char **env);
char	**get_input(void);
int		env_var_position(char **env, char *variable_name);
char	*env_var_value(char **env, char *variable_name);
char	**prep_env_vec(char **sys_env, int ac);

int main(int arr_c, char **av, char **sys_env)
{
	static int		ac;
    char **input_split;
	char *commands[4];
	functions exec[3];
	char **env;

	exec[0] = &echo;
	exec[1] = &cd;
	exec[2] = &pwd;
	commands[0] = "echo";
	commands[1] = "cd";
	commands[2] = "pwd";
	commands[3] = NULL;

	while (sys_env[ac] != NULL)
		ac++;	// This can be renamed envc
	env = prep_env_vec(sys_env, ac);	
    while (1)
    {
		input_split = get_input(); 
		if (*input_split == NULL)
			continue;
		if (ft_strcmp(*input_split, "exit") == 0)
			break;
		int i = 0;
		while (i < 2){
			if (commands[i] != NULL && ft_strcmp(input_split[0], commands[i]) == 0)	
				break;
			i++;
		}
		if (commands[i] == NULL)
		{
			ft_putstr(*input_split);
			ft_putendl(" Does not exist");
		}
		else
		{
			exec[i](input_split + 1, env);
		}
	}
	int i = 0;
	while (env[i] != NULL)
	{
		ft_putendl(env[i]);
		free(env[i++]);
	}
	return (0);
}

void	set_env_var(char **env, char *var_name, char *new_val)
{
	int pos;
	char *new_env_var;
	char *tmp;

	// start a new environment variable.
	new_env_var = ft_strdup(var_name);
	ft_putendl(new_env_var);
	tmp = new_env_var;
	new_env_var = ft_strjoin(new_env_var, "=");
	free(tmp);

	// join the new value to the string.
	ft_putendl(new_env_var);
	tmp = new_env_var;
	new_env_var = ft_strjoin(new_env_var, new_val);
	free(tmp);

	pos = env_var_position(env,var_name);
	if (pos != -1)
	{
		char *tmp = env[pos];
		env[pos] = new_env_var;
		free(tmp);
	}
	// this is where the adding a variable will be placed.
}

// This function is used to create a copy of the environment vector
// giving me the ability to create, edit and remove environment variables.
char	**prep_env_vec(char **sys_env, int ac)
{
	char **env;
	int	i;

	env = (char **)malloc(sizeof(char *) * (ac * 2));
	i = 0;
	while (sys_env[i] != NULL)
	{
		env[i] = ft_strdup(sys_env[i]);
		i++;
	}
	env[i] = NULL;
	return (env);
}

// This function is used to get the value of a specific environment variable.
char	*env_var_value(char **env, char *variable_name)
{
	char *out;
	int pos;

	pos = env_var_position(env, variable_name);
	out = ft_strdup(env[pos] + ft_strlen(variable_name) + 1);
	return (out);
}

// This will searh for the variable in the set of environment variables.
int		env_var_position(char **env, char *variable_name)
{
	int pos;

	pos = 0;
	while (env[pos] != NULL){
		if (ft_strncmp(env[pos], variable_name, ft_strlen(variable_name)) == 0){
			return (pos);
		}
		pos++;
	}
	return (-1);
}

// This is where all the cool input tricks will processed.
char	**get_input()
{
	char **input_split;
	char *input;
	int ret;

	ft_putstr("$>");
	ret = get_next_line(1, &input);
	input_split = ft_strsplit(input, ' ');
	free(input);
	return (input_split);
}

void	pwd(char **av, char **env)
{
	int i = 0;
	static char cwd[255];

	while (av[i] != NULL)
	{
		i++;
	}
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		ft_putendl("pwd error");
	}
	else
		ft_putendl(cwd);
}

/* In order for 'cd' and other functionalities to work properly
 * I need to handle and process the environment variables */
void	cd(char **av, char **env)
{
	int ret;
	int i = 0;
	char *path;


	// this can be moved to another fucntion of its own.
	while (av[i] != NULL)
	{
		i++;
	}
	// I need to handle the HOME environment variable.
	// After which i can start processing the other corner cases of cd.
	if (i == 0 || ft_strcmp(av[0], "~") == 0)
		path = env_var_value(env, "HOME");
	else
		path = av[0];
	if ((ret = chdir(path)) == -1)
	{
		ft_putendl("Error changing directory");
	}
	char *pwd = env_var_value(env, "PWD");
	char cwd[255];
	set_env_var(env, "OLDPWD", pwd);
	getcwd(cwd, sizeof(cwd));
	set_env_var(env, "PWD", cwd);
	free(pwd);
	free(path);
	/* pwd(av+i, env); */
}

// I need to handle the environment variables before i can 
// make echo work properly.
void	echo(char **av, char **env)
{
	while (*av != NULL)
	{
		ft_putstr(*av);
		ft_putstr(" ");
		av++;
	}
	ft_putendl("");
}
