/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/21 21:22:15 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/10/22 16:07:07 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_signal	g_signal;

static void	levelup_shell(t_shell *shell)
{
	char	**commands;
	char	*temp;
	char	*levelstring;
	int		lvl;

	commands = (char **)malloc(sizeof(char *) * 3);
	commands[0] = ft_strdup("export");
	lvl = ft_atoi(getenv("SHLVL"));
	lvl += 1;
	levelstring = ft_itoa(lvl);
	temp = ft_strjoin("SHLVL=", levelstring);
	free(levelstring);
	commands[1] = ft_strdup(temp);
	free(temp);
	commands[2] = NULL;
	shell_export(commands, shell);
	free_array(commands);
}

static void	init_shell_values(t_shell *shell, char **envp)
{
	shell->evs = copy_evs(envp);
	shell->in = dup(STDIN);
	shell->out = dup(STDOUT);
	shell->exit = 0;
	shell->rv = 0;
	shell->no_exec = 0;
	reset_fds(shell);
	levelup_shell(shell);
}

void	ft_skip_spacenl(const char *str, int *i)
{
	while ((str[*i] == ' ' || str[*i] == '\t' || str[*i] == '\n')
	|| (str[*i] == '\r' || str[*i] == '\v' || str[*i] == '\f'))
		(*i)++;
}

void	free_tokens(t_token *start)
{
	while (start && start->next)
	{
		start = start->next;
		if (start->prev)
			ft_memdel(start->prev);
	}
	if (start)
		free(start);
}

void	operator_redirect(t_shell *shell, t_token *token, int type)
{
	ft_close(shell->fdout);
	if (type == TRUNC)
		shell->fdout = open(token->str, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	else
		shell->fdout = open(token->str, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	if (shell->fdout == -1)
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(token->str, STDERR);
		ft_putendl_fd(": No such file or directory", STDERR);
		shell->rv = 1;
		shell->no_exec = 1;
		return ;
	}
	dup2(shell->fdout, STDOUT);
}

void	operator_input(t_shell *shell, t_token *token)
{
	ft_close(shell->fdin);
	shell->fdin = open(token->str, O_RDONLY, S_IRWXU);
	if (shell->fdin == -1)
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(token->str, STDERR);
		ft_putendl_fd(": No such file or directory", STDERR);
		shell->rv = 1;
		shell->no_exec = 1;
		return ;
	}
	dup2(shell->fdin, STDIN);
}

int	operator_pipe(t_shell *shell)
{
	pid_t	pid;
	int		fds[2];

	pipe(fds);
	pid = fork();
	if (pid == 0)
	{
		ft_close(fds[1]);
		dup2(fds[0], STDIN);
		shell->pipin = fds[0];
		shell->pid = -1;
		shell->parent = 0;
		shell->no_exec = 0;
		return (2);
	}
	ft_close(fds[0]);
	dup2(fds[1], STDOUT);
	shell->pipout = fds[1];
	shell->pid = pid;
	shell->last = 0;
	return (1);
}

char	**create_command_array(t_token *start)
{
	t_token *token;
	char	**array;
	int		i;

	if (start == NULL)
		return (NULL);
	token = start->next;
	i = 2;
	while (token && token->type < TRUNC)
	{
		token = token->next;
		i++;
	}
	array = (char **)malloc(sizeof(char *) * i);
	if (!array)
		return (NULL);
	token = start->next;
	array[0] = start->str;
	i = 1;
	while (token && token->type < TRUNC)
	{
		array[i] = token->str;
		token = token->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}

int		has_pipe(t_token *token)
{
	while (token && is_type(token, END) == 0)
	{
		if (is_type(token, PIPE))
			return (1);
		token = token->next;
	}
	return (0);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (array == NULL)
		return ;
	while (array[i])
	{
		if (array[i])
			free(array[i]);
		i++;
	}
	if (array)
		free(array);
}

int	builtin_check(char *command)
{
	if (ft_strcmp(command, "cd") == 0)
		return (1);
	if (ft_strcmp(command, "echo") == 0)
		return (1);
	if (ft_strcmp(command, "env") == 0)
		return (1);
	if (ft_strcmp(command, "export") == 0)
		return (1);
	if (ft_strcmp(command, "pwd") == 0)
		return (1);
	if (ft_strcmp(command, "unset") == 0)
		return (1);
	if (ft_strcmp(command, "unsetenv") == 0)
		return (1);
	if (ft_strcmp(command, "setenv") == 0)
		return (1);	
	return (0);
}

void	run_commands(t_shell *shell, t_token *token)
{
	char 	**commands;
	int		i;

	if (shell->charge == 0)
		return ;
	commands = create_command_array(token);
	i = 0;
	expand_commands(shell, commands);
	if (commands && ft_strcmp(commands[0], "exit") == 0 && has_pipe(token) == 0)
		shell_exit(shell, commands);
	else if (commands && builtin_check(commands[0])) 
		shell->rv = execute_builtin(commands, shell);
	else if (commands)
		shell->rv = execute_bin(commands, shell);
	if (commands && shell->rv != -1)
		free_array(commands);
	ft_close(shell->pipin);
	ft_close(shell->pipout);
	shell->pipin = -1;
	shell->pipout = -1;
	shell->charge = 0;
}

void	shell_execute(t_shell *shell, t_token *token)
{
	t_token *prev;
	t_token *next;
	int		pipe;

	prev = previous_separator(token, 0);
	next = next_separator(token, 0);
	pipe = 0;
	if (is_type(prev, TRUNC))
		operator_redirect(shell, token, TRUNC);
	else if (is_type(prev, APPEND))
		operator_redirect(shell, token, APPEND);
	else if (is_type(prev, INPUT))
		operator_input(shell, token);
	else if (is_type(prev, PIPE))
		pipe = operator_pipe(shell);
	if (next && is_type(next, END) == 0 && pipe != 1)
		shell_execute(shell, next->next);
	if ((is_type(prev, END) || is_type(prev, PIPE) || !prev) \
			&& pipe != 1 && shell->no_exec == 0)
		run_commands(shell, token);
}

void	minishell(t_shell *shell)
{
	t_token *token;
	int		status;

	token = next_run(shell->start, 0);
	if (is_types(shell->start, "TAI"))
		token = shell->start->next;
	while (token && shell->exit == 0)
	{
		shell->charge = 1;
		shell->parent = 1;
		shell->last = 1;
		shell_execute(shell, token);
		reset_std(shell);
		close_fds(shell);
		reset_fds(shell);
		waitpid(-1, &status, 0);
		status = WEXITSTATUS(status);
		if (shell->last == 0)
			shell->rv = status;
		if (shell->parent == 0)
		{
			free_tokens(shell->start);
			exit(shell->rv);
		}
		shell->no_exec = 0;
		token = next_run(token, 1);
	}
}

char	**copy_evs(char **inputs)
{
	int		i;
	char	**ret;

	i = 0;
	while (inputs[i])
		i++;
	ret = malloc((i + 1) * (sizeof(char *)));
	if (!ret)
		return (NULL);
	i = 0;
	while (inputs[i])
	{
		ret[i] = ft_strdup(inputs[i]);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	if (argc > 1)
	{
		ft_printf_fd(2, "minishell: %s: No such file \
				or directory\n", argv[1]);
		return (127);
	}
	init_shell_values(&shell, envp);
	ft_printf("Hi %s! Welcome to ~~minishell~~. ", getenv("USER"));
	ft_printf("Enter 'exit' at any time to leave.\n");
	ft_printf("_______________________________________________________\n");
	while (shell.exit == 0)
	{
		init_signal();
		signal(SIGINT, &signal_int_handler);
		signal(SIGQUIT, &signal_quit_handler);
		parse(&shell);
		if (shell.start != NULL && check_line(&shell, shell.start))
			minishell(&shell);
		free_tokens(shell.start);
	}
	free_array(shell.evs);
	return (shell.rv);
}
