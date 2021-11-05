/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_builtins.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/21 14:28:50 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/11/05 16:05:52 by nkuipers      ########   odam.nl         */
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

static int	n_check(char *command)
{
	int	i;

	i = 2;
	if (ft_strncmp(command, "-n", 2) != 0)
		return (0);
	while (command[i])
	{
		if (command[i] != 'n' && command[i] != '\0')
			return (0);
		i++;
	}
	return (1);
}

int	shell_echo(char **commands)
{
	int	i;
	int	nflag;

	i = 1;
	nflag = 0;
	if (!commands[1])
		ft_printf("\n");
	while (commands[i])
	{
		if (n_check(commands[i]) == 1)
			nflag = 1;
		else if (commands[i] == NULL)
			return (0);
		else if (commands[i + 1] == NULL && nflag == 0)
			ft_printf("%s\n", commands[i]);
		else if (commands[i + 1] == NULL)
			ft_printf("%s", commands[i]);
		else
			ft_printf("%s ", commands[i]);
		i++;
	}
	return (0);
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
