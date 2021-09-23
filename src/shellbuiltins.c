/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shellbuiltins.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/23 16:06:15 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/10/01 16:20:47 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** This is a recreation of pwd. We just call getcwd() which returns a string.
** The argument 1024 does nothing when the first argument is NULL, but we need
** to put it in anyway because the person who wrote it is bad at his job.
*/

int			shell_pwd(t_shell *shell)
{
	char	*path;

	(void)shell;
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
	char	*temp;
	char	*pwd;
	int		j;

	j = find_ev(evs, "PWD=");
	pwd = getcwd(NULL, 1024);
	free(pwd);
	temp = evs[j];
	evs[j] = ft_strjoin("PWD=", pwd);
	free(temp);
	temp = evs[i];
	evs[i] = ft_strjoin("OLDPWD=", old);
	free(old);
	free(temp);
	return (0);
}

int			shell_cd(t_shell *shell)
{
	int		i;
	char	*old;

	old = getcwd(NULL, 1024);
	if (shell->args[1] == NULL)
	{
		i = find_ev(shell->evs, "HOME=");
		chdir(&((shell->evs)[i][5]));
	}
	i = find_ev(shell->evs, "OLDPWD=");
	if (shell->args[1] != NULL)
	{
		if (ft_strncmp(shell->args[1], "-", 2) == 0)
		{
			chdir(&((shell->evs)[i][7]));
			shell_pwd(shell);
		}
		else if (chdir(shell->args[1]) != 0)
		{
			free(old);
			return (ft_printf("That folder does not exist.\n"));
		}
	}
	return (set_new_pwd(shell->evs, i, old));
}

/*
** Wrote a little help function to show off what we can do.
*/

int			shell_help(t_shell *shell)
{
	(void)shell;
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

int			shell_env(t_shell *shell)
{
	int		i;
	int		j;

	i = 0;
	while (shell->evs[i])
	{
		j = 0;
		while (shell->evs[i][j + 1] != '\0')
			j++;
		if (shell->evs[i][j] != '=')
			ft_printf("%s\n", shell->evs[i]);
		i++;
	}
	return (0);
}
