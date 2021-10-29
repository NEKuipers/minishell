/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/21 21:22:15 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/10/29 11:13:54 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_signal	g_signal;

char	**create_command_array(t_token *start)
{
	t_token	*token;
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
	token = start->next;
	array[0] = ft_strdup(start->str);
	i = 1;
	while (token && token->type < TRUNC)
	{
		array[i] = ft_strdup(token->str);
		token = token->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}

void	run_commands(t_shell *shell, t_token *token)
{
	char	**commands;

	if (shell->charge == 0)
		return ;
	commands = create_command_array(token);
	if (ft_strcmp(commands[0], "cat") == 0 || ft_strcmp(commands[0], "head") \
		== 0 || ft_strcmp(commands[0], "tail") == 0)
		g_signal.cht = 1;
	if (commands && ft_strcmp(commands[0], "exit") == 0 \
			 && has_pipe(token) == 0)
		shell_exit(shell, commands);
	else if (commands && builtin_check(commands[0]))
		shell->rv = execute_builtin(commands, shell);
	else if (commands)
		shell->rv = execute_bin(commands, shell, token);
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
	t_token	*prev;
	t_token	*next;
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
	t_token	*token;
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
		full_fd_reset(shell);
		waitpid(-1, &status, 0);
		status = WEXITSTATUS(status);
		if (shell->last == 0)
			shell->rv = status;
		if (shell->parent == 0)
		{
			free_tokens(token);
			exit(shell->rv);
		}
		shell->no_exec = 0;
		token = next_run(token, 1);
	}
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
		if (shell.start != NULL && check_syntax(&shell, shell.start))
			minishell(&shell);
		free_tokens(shell.start);
	}
	free_array(shell.evs);
	return (shell.rv);
}
