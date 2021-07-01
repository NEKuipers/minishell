/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/21 21:22:16 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/07/01 12:51:48 by nkuipers      ########   odam.nl         */
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
	int				rv;
	char			type;
	struct s_ops	*next;
}					t_ops;

typedef struct		s_pipeline
{
	int				*fd[2];
	int				pipecount;
	pid_t			pid;
	int				amount;
}					t_pipeline;

typedef struct		s_shell
{
	t_list			*ops;
	char			**args;
	char			**evs;
	int				rv;
	int				fds[2];
	int				count;
	int				stdin;
	int				stdout;
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
void				dupclose_fd(int fd, int sec_fd);

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
int					run_cmds(t_shell *shell, t_list *tlist);
void				clear_ops(void *ops);

int					operator_exec(t_list *tlist, t_shell *shell, t_pipeline *pipeline);
int					operator_redirect_output(t_list *tlist, t_shell *shell);
int					operator_append_output(t_list *tlist, t_shell *shell);
int					operator_pipe(t_list *tlist, t_shell *shell, t_pipeline *pipeline);
int					operator_redirect_input(t_list *tlist, t_shell *shell);
void				pipe_error(t_list *tlist, t_shell *shell);

#endif
