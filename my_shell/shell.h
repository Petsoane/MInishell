/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpetsoan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 12:07:21 by lpetsoan          #+#    #+#             */
/*   Updated: 2019/09/09 12:52:55 by lpetsoan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H
# define COMMANDS 7
# define FUNCTIONS COMMANDS - 1
# define PROMPT "$>"
# define BUILTS "BUILTINFUNC"
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef void (*functions)();

int		parse_command(char **av, char **env);
void	builtin_functions(functions *exec);
void	prep_commands(char **av);
void	echo(char **av, char **env);
void	cd(char **av, char **env);
void	pwd(char **av, char **env);
int		env_var_pos(char **env, char *var_name);
char	*env_var_value(char **env, char *var_name);
void	set_env_var(char **env, char *var_name, char *val);
void	print_env(char **env);
void	environment(char **env, char **av);
void	set_env(char **env, char *new_var);
int		valid_env_var(char *new_var);
int		env_var_count(char **env);
void	unset_env_var(char **env, char **av);
char	**get_input(char **env);
char	*get_bin_path(char *path_var, char *bin_name);
void	child_process(char **argv, char **env, char *bin_path);
void	run_bin(char **argv, char **env);
void	which(char **env, char **argv);
void	add_var_builtins(char **env, char **commands);
int		is_builtins(char **env, char *command, char **split);

#endif
