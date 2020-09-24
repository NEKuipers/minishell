/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/21 21:22:16 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/09/24 11:10:22 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>
# include <unistd.h>
# include "../lib/libft/libft.h"
# include "../lib/ft_printf/includes/ft_printf.h"

void    shell_loop(char **evs);
char    **copy_evs(char **inputs);
int     shell_exit(char **args, char **evs);
int     shell_cd(char **args, char **evs);
int     shell_echo(char **args, char **evs);
int     shell_env(char **args, char **evs);
int     shell_ls(char **args, char **evs);
int     shell_pwd(char **args, char **evs);
int     shell_help(char **args, char **evs);
void    free_args(char **args);
char	**ft_token(char const *s, char c, char d);

#endif
