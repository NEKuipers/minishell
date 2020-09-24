/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shellbuiltins.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/23 16:06:15 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/09/24 10:55:38 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		shell_pwd(char **args, char **evs)
{
	char *path;

	(void)args;
	(void)evs;
	path = getcwd(NULL, 1024);
	ft_printf("%s\n", path);
	free(path);
	return (0);
}

int		shell_exit(char **args, char **evs)
{
	free_args(evs);
	free_args(args);
	ft_printf("Goodbye.\n");
	exit(0);
	return (0);
}

int		shell_cd(char **args, char **evs)
{
	(void)evs;
	if (!args[1])
		ft_printf("Please specify which directory you want to change to.\n");
	else
	{
		if (chdir(args[1]) != 0)
			ft_printf("That folder does not exist.\n");
	}
	return (0);
}

int		shell_help(char **args, char **evs)
{
	(void)args;
	(void)evs;
	ft_printf("You can try one of the following commands:\n");
	ft_printf(" - cd to change directory\n");
	ft_printf(" - env to print environment variables\n");
	ft_printf(" - pwd to print working directory\n");
	ft_printf(" - exit to exit the shell.\n");
	return (0);
}

int		shell_env(char **args, char **evs)
{
	int i;

	i = 0;
	(void)args;
	while (evs[i])
	{
		ft_printf("%s\n", evs[i]);
		i++;
	}
	return (0);
}
