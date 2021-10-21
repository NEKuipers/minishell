/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/21 21:22:16 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/10/21 17:07:25 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include <string.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <dirent.h>
# include <errno.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../lib/libft/libft.h"

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define EMPTY 0
# define CMD 1
# define ARG 2
# define TRUNC 3
# define APPEND 4
# define INPUT 5
# define PIPE 6
# define END 7

# define BUFF_SIZE 4096

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

typedef struct s_signal
{
	int				sigint;
	int				sigquit;
	int				exit_status;
	pid_t			pid;
}					t_signal;

typedef struct s_shell
{
	t_token			*start;
	char			**evs;
	int				in;
	int				out;
	int				fdin;
	int				fdout;
	int				pipin;
	int				pipout;
	int				pid;
	int				charge;
	int				parent;
	int				last;
	int				rv;
	int				exit;
	int				no_exec;
}					t_shell;

void				init_signal(void);

void				ft_close(int fd);
void				reset_std(t_shell *shell);
void				close_fds(t_shell *shell);
void				reset_fds(t_shell *shell);

void				ft_skip_spacenl(const char *str, int *i);

int					quotes(char *line, int index);
int					quote_check(t_shell *shell, char **line);
int					is_separator(char *line, int i);
char				*space_alloc(char *line);
char				*space_out_line(char *line);
void				skip_space(const char *str, int *i);
t_token				*next_separator(t_token *token, int skip);
t_token				*previous_separator(t_token *token, int skip);
t_token				*next_run(t_token *token, int skip);
int					is_type(t_token *token, int type);
int					find_separator(char *line, int i);
int					is_types(t_token *token, char *types);
int					is_last_valid_arg(t_token *token);
void				squish_args(t_shell *shell);
void				parse(t_shell *shell);
int					check_line(t_shell *shell, t_token *token);
t_token				*create_tokens(char *line);
void				apply_token_type(t_token *token, int separator);
t_token				*next_token(char *line, int *i);
int					next_alloc(char *line, int *i);

void				free_tokens(t_token *token);
void				free_array(char **array);

char				**set_new_env(char **evs, char *arg);
int					find_ev(char **evs, char *target);
char				**copy_evs(char **inputs);
char				**expand_commands(t_shell *shell, char **args);

void				minishell(t_shell *shell);
void				shell_execute(t_shell *shell, t_token *token);
int					execute_builtin(char **commands, t_shell *shell);
int					shell_pwd(void);
int					shell_echo(char **commands);
int					shell_env(t_shell *shell);
int					shell_cd(char **commands, t_shell *shell);
int					shell_export(char **commands, t_shell *shell);
void				shell_exit(t_shell *shell, char **commands);
int					shell_unset(char **commands, t_shell *shell);
int					execute_bin(char **commands, t_shell *shell);

void				signal_int_handler(int code);
void				signal_quit_handler(int code);
void				init_signal(void);

//Added in beta 3
//_____________________________________________________________________________
char				*repl_process(char *in, char **env);
//_____________________________________________________________________________
extern t_signal	g_signal;

#endif
