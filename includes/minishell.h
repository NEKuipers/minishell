/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/21 21:22:16 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/10/15 14:47:28 by nkuipers      ########   odam.nl         */
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

typedef struct		s_ops
{
	char			*operation;
	char			**args;
	int				in_quotes;
	int				pipefds[2];
	int				rv;
	char			type;
	struct s_ops	*next;
}					t_ops;

typedef struct		s_shell
{
	char			**operations;
	char			**args;
	char			**evs;
	int				rv;
}					t_shell;

int					shell_cat(char **args, char **evs);
int					shell_cd(char **args, char **evs);
int					shell_echo(char **args, char **evs);
int					shell_env(char **args, char **evs);
int					shell_execpath(char **args, char **evs);
int					shell_execute(t_shell *shell, char **args);
int					shell_exit(char **args, char **evs);
int					shell_export(char **args, char ***evs);
int					shell_help(char **args, char **evs);
void				shell_loop(t_shell *shell);
int					shell_pwd(char **args, char **evs);
int					shell_unset(char **args, char ***evs);

void				ctrlchandler(int n);
void				ctrlbshandler(int n);

void				free_args(char **args);
char				**copy_evs(char **inputs);
char				**ft_token(char const *s, char c, char d);
char				**transl_env(t_shell *shell, char **args);
int					find_ev(char **evs, char *target);
size_t				ft_evlen(char *ev);
char				*insert_rv(char *rv, char *arg);
char				**remove_env(char **evs, char *arg);
char				**set_new_env(char **evs, char *arg);
int					parse_inputstring(t_shell *shell, char *input);

#endif
