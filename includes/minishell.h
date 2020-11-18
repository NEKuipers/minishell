/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/21 21:22:16 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/11/18 14:24:26 by nkuipers      ########   odam.nl         */
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
	char			type[999];
	struct s_ops	*next;
}					t_ops;

typedef struct		s_shell
{
	t_list			*ops;
	char			**args;
	char			**evs;
	int				rv;
	int				in;
	int				out;
}					t_shell;

int					shell_cd(t_shell *shell);
int					shell_echo(t_shell *shell);
int					shell_env(t_shell *shell);
int					shell_execpath(t_shell *shell);

int					shell_execute(t_shell *shell, char **args);
int					shell_exit(t_shell *shell);
int					shell_export(t_shell *shell);
int					shell_help(t_shell *shell);
void				shell_loop(t_shell *shell);
int					shell_pwd(t_shell *shell);
int					shell_unset(t_shell *shell);

void				ctrlchandler(int n);
void				ctrlbshandler(int n);
void				ft_close_fd(int fd);
void				reset_std_fds(t_shell *shell);

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
