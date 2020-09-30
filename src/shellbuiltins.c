/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shellbuiltins.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/23 16:06:15 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/09/30 12:54:56 by nkuipers      ########   odam.nl         */
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
** Again, a systemcall makes our work easier. Chdir changes directory for us,
** as long as it actually exists. Problem is, we need to update both PWD and
** OLDPWD after every time we change directory.
** cd without arguments reverts to Home. cd with '-' flag will direct us to
** OLDPWD and print wd afterwards.
*/

static int	set_new_pwd(char **evs, int i, char *old)
{
	char *temp;
	char *pwd;
	int j;

	while (ft_strncmp(evs[j], "PWD=", 4) != 0)
		j++;
	pwd = getcwd(NULL, 1024);
	temp = evs[j];
	evs[j] = ft_strjoin("PWD=", pwd);
	free(temp);
	temp = evs[i];
	evs[i] = ft_strjoin("OLDPWD=", old);
	free(temp);
	return (0);
}

int			shell_cd(char **args, char **evs)
{
	int		i;
	char	*old;

	i = 0;
	old = getcwd(NULL, 1024);
	if (args[1] == NULL)
	{
		while (ft_strncmp(evs[i], "HOME=", 5) != 0)
			i++;
		chdir(&evs[i][5]);
	}
	i = 0;
	while (ft_strncmp(evs[i], "OLDPWD=", 7) != 0)
		i++;
	if (args[1] != NULL)
	{
		if (ft_strncmp(args[1], "-", 2) == 0)
		{
			chdir(&evs[i][7]);
			shell_pwd(args, evs);
		}
		else if (chdir(args[1]) != 0)
			return (ft_printf("That folder does not exist.\n"));
	}
	return (set_new_pwd(evs, i, old));
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
