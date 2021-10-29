/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_cd.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/30 09:47:34 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/10/29 12:29:53 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	shell_cd(char **c, t_shell *shell)
{
	int		i;
	char	*old;

	old = getcwd(NULL, 1024);
	if (c[1] == NULL || ft_strncmp("~\0", c[1], 2) == 0)
	{
		i = find_ev(shell->evs, "HOME=");
		chdir(&((shell->evs)[i][5]));
	}
	i = find_ev(shell->evs, "OLDPWD=");
	if (c[1] != NULL && ft_strncmp("~\0", c[1], 2) != 0)
	{
		if (ft_strncmp(c[1], "-", 2) == 0)
		{
			chdir(&((shell->evs)[i][7]));
			shell_pwd();
		}
		else if (chdir(c[1]) != 0)
		{
			free(old);
			ft_printf("minishell: cd: %s: No such file or directory\n", c[1]);
			return (1);
		}
	}
	return (set_new_pwd(shell->evs, i, old));
}
