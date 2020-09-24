/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/21 21:22:16 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/09/24 14:56:07 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>
# include "../lib/libft/libft.h"
# include "../lib/ft_printf/includes/ft_printf.h"

int		shell_cat(char **args, char **evs);
int		shell_cd(char **args, char **evs);
int		shell_echo(char **args, char **evs);
int		shell_env(char **args, char **evs);
int		shell_execpath(char **args, char **evs);
int		shell_exit(char **args, char **evs);
int		shell_help(char **args, char **evs);
void	shell_loop(char **evs);
int		shell_pwd(char **args, char **evs);

void	ctrlchandler(int n);

void	free_args(char **args);
char	**copy_evs(char **inputs);
char	**ft_token(char const *s, char c, char d);
char	*joinpaths(char *s1, char *s2);

#endif
