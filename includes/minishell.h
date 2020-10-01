/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/21 21:22:16 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/10/01 10:08:22 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include "../lib/libft/libft.h"
# include "../lib/ft_printf/includes/ft_printf.h"

int		shell_cat(char **args, char **evs);
int		shell_cd(char **args, char **evs);
int		shell_echo(char **args, char **evs);
int		shell_env(char **args, char **evs);
int		shell_execpath(char **args, char **evs);
int		shell_exit(char **args, char **evs);
int		shell_export(char **args, char **evs);
int		shell_help(char **args, char **evs);
void	shell_loop(char **evs);
int		shell_pwd(char **args, char **evs);

void	ctrlchandler(int n);
void	ctrlbshandler(int n);

void	free_args(char **args);
char	**copy_evs(char **inputs);
char	**ft_token(char const *s, char c, char d);
char	**transl_env(char **args, char **evs);
int		find_ev(char **evs, char *target);

#endif
