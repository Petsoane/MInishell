/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpetsoan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 12:07:21 by lpetsoan          #+#    #+#             */
/*   Updated: 2019/09/04 12:34:15 by lpetsoan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H
# define COMMANDS 4
# define FUNCTIONS COMMANDS - 1
# define PROMPT "$>"
# include "libft/libft.h"

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

#endif