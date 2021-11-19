/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_builtins.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/21 14:28:50 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/11/19 10:22:10 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	shell_pwd(void)
{
	char	*path;

	path = getcwd(NULL, BUFF_SIZE);
	if (path)
	{
		ft_printf("%s\n", path);
		free(path);
		return (0);
	}
	return (1);
}

int	shell_echo(char **commands)
{
	int	i;
	int	nflag;

	i = 1;
	nflag = 0;
	while (commands[i] && ft_strncmp(commands[i], "-n", 2) == 0 && \
		only_has(commands[i] + 1, 'n'))
	{
		nflag = 1;
		i++;
	}
	while (commands[i])
	{
		if (commands[i + 1] == NULL)
			ft_printf("%s", commands[i]);
		else
			ft_printf("%s ", commands[i]);
		i++;
	}
	if (nflag == 0)
		ft_printf("\n");
	return (0);
}

void	shell_exit(t_shell *shell, char **commands)
{
	shell->exit = 1;
	if (commands[1] && ft_strisnum(commands[1]) == 0)
	{
		shell->rv = 255;
		ft_printf_fd(2, "exit\nminishell:");
		ft_printf_fd(2, "exit: %s: numeric argument required\n", commands[1]);
	}
	else if (commands[1] && commands[2])
	{
		shell->rv = 1;
		shell->exit = 0;
		ft_printf_fd(STDERR, "exit\nminishell: exit: too many arguments\n");
	}
	else
	{
		if (commands[1])
			shell->rv = ft_atoi(commands[1]);
		else
			shell->rv = 0;
		ft_printf_fd(0, "exit\n");
	}
}

int	execute_builtin(char **commands, t_shell *shell)
{
	if (ft_strcmp(commands[0], "toggle") == 0)
		return (shell_toggle(commands));
	if (ft_strcmp(commands[0], "cd") == 0 || \
	ft_strcmp(commands[0], "..") == 0 || ft_strcmp(commands[0], ".") == 0)
		return (shell_cd(commands, shell));
	if (ft_strcmp(commands[0], "echo") == 0)
		return (shell_echo(commands));
	if (ft_strcmp(commands[0], "pwd") == 0)
		return (shell_pwd());
	if (ft_strcmp(commands[0], "env") == 0)
		return (shell_env(shell));
	if (ft_strcmp(commands[0], "export") == 0 || \
			ft_strcmp(commands[0], "setenv") == 0)
		return (shell_export(commands, shell));
	if (ft_strcmp(commands[0], "unset") == 0 || \
			ft_strcmp(commands[0], "unsetenv") == 0)
		return (shell_unset(commands, shell));
	return (0);
}

int	builtin_check(char *command)
{
	if (ft_strcmp(command, "toggle") == 0)
		return (1);
	if (ft_strcmp(command, "..") == 0)
		return (1);
	if (ft_strcmp(command, ".") == 0)
		return (1);
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
