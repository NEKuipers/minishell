/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_builtins.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/21 14:28:50 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/10/21 14:33:15 by nkuipers      ########   odam.nl         */
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
	while (commands[i])
	{
		if (ft_strncmp(commands[i], "-n", 3) == 0)
		{
			i++;
			nflag = 1;
		}
		if (commands[i] == NULL)
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

void	shell_exit(t_shell *shell, char **commands)
{
	shell->exit = 1;
    ft_printf("exit\n");
	if (commands[1] && commands[2])
	{
		shell->rv = 1;
		shell->exit = 0;
		ft_printf_fd(STDERR, "minishell: exit: too many arguments\n");
	}
	else if (commands[1] && ft_strisnum(commands[1]) == 0)
	{
		shell->rv = 255;
		ft_printf_fd(STDERR, "minishell: exit: %s: numeric argument required\n"\
			, commands[1]);
	}
	else if (commands[1])
		shell->rv = ft_atoi(commands[1]);
	else
		shell->rv = 0;
}

int	execute_builtin(char **commands, t_shell *shell)
{
	int	returnvalue;

	returnvalue = 0;
	if (ft_strcmp(commands[0], "cd") == 0)
		returnvalue = shell_cd(commands, shell);
	if (ft_strcmp(commands[0], "echo") == 0)
		returnvalue = shell_echo(commands);
	if (ft_strcmp(commands[0], "pwd") == 0)
		returnvalue = shell_pwd();
	if (ft_strcmp(commands[0], "env") == 0)
		shell_env(shell);
	if (ft_strcmp(commands[0], "export") == 0 || \
			ft_strcmp(commands[0], "setenv") == 0)
		returnvalue = shell_export(commands, shell);
	if (ft_strcmp(commands[0], "unset") == 0 || \
			ft_strcmp(commands[0], "unsetenv") == 0)
		returnvalue = shell_unset(commands, shell);
	return (0);
}
