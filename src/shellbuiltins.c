/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shellbuiltins.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/23 16:06:15 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/09/24 16:02:18 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** This is a recreation of pwd. We just call getcwd() which returns a string.
** The argument 1024 does nothing when the first argument is NULL, but we need
** to put it in anyway because the person who wrote it is bad at his job.
*/

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

/*
** Free the malloced stuff and exit.
*/

int		shell_exit(char **args, char **evs)
{
	free_args(evs);
	free_args(args);
	ft_printf("Goodbye.\n");
	exit(0);
	return (0);
}

/*
** Again, a systemcall makes our work easier. Chdir changes directory for us,
** as long as one is given and it actually exists.
*/

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

/*
** Wrote a little help function to show off what we can do.
*/

int		shell_help(char **args, char **evs)
{
	(void)args;
	(void)evs;
	ft_printf("You can try one of the following commands:\n");
	ft_printf(" - cd to change directory\n");
	ft_printf(" - env to print environment variables\n");
	ft_printf(" - ls to list the contents of the current directory\n");
	ft_printf(" - pwd to print working directory\n");
	ft_printf(" - touch [filename] to create a file\n");
	ft_printf(" - exit to exit the shell.\n");
	return (0);
}

/*
**	The command env prints all the environment variables with a value.
*/

int		shell_env(char **args, char **evs)
{
	int i;
	int j;

	i = 0;
	(void)args;
	while (evs[i])
	{
		j = 0;
		while (evs[i][j + 1] != '\0')
		{
			j++;
		}
		if (evs[i][j] != '=')
			ft_printf("%s\n", evs[i]);
		i++;
	}
	return (0);
}
