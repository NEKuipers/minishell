/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_cd.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/30 09:47:34 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/11/03 11:50:27 by nkuipers      ########   odam.nl         */
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

static int	shell_cd_do(char **c, t_shell *shell)
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

int	shell_cd(char **c, t_shell *shell)
{
	char **newcmd;
	
	if (ft_strcmp(c[0], ".") == 0)
		return (0);
	if (ft_strcmp(c[0], "..") == 0)
	{
		newcmd = (char **)malloc(sizeof(char *) * 3);
		newcmd[0] = ft_strdup("cd");
		newcmd[1] = ft_strdup("..");
		newcmd[2] = NULL;
		free_array(c);
		return (shell_cd_do(newcmd, shell));
	}
	else
		return (shell_cd_do(c, shell));
}
