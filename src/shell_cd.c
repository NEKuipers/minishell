/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_cd.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/30 09:47:34 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/11/18 12:47:12 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	set_new_oldpwd(t_shell *shell, int i, char *old)
{
	char	*temp;

	if (i != -1)
	{
		temp = shell->evs[i];
		shell->evs[i] = ft_strjoin("OLDPWD=", old);
	}
	else
	{
		temp = ft_strjoin("OLDPWD=", old);
		replace_env(shell, temp, ' ');
	}
	free(temp);
	free(old);
}

static int	set_new_pwd(t_shell *shell, int i, char *old)
{
	char	*temp;
	char	*pwd;
	int		j;

	j = find_ev(shell->evs, "PWD=");
	pwd = getcwd(NULL, 1024);
	if (j != -1)
	{
		temp = shell->evs[j];
		shell->evs[j] = ft_strjoin("PWD=", pwd);
	}
	else
	{
		temp = ft_strjoin("PWD=", pwd);
		replace_env(shell, temp, ' ');
	}
	free(temp);
	free(pwd);
	set_new_oldpwd(shell, i, old);
	return (0);
}

static int	shell_previous_fail(char *old)
{
	ft_printf_fd(2, "minishell: cd: OLDPWD not set\n");
	free (old);
	return (1);
}

static int	shell_cd_do(char **c, t_shell *shell)
{
	int		i;
	char	*old;

	old = getcwd(NULL, 1024);
	if (c[1] == NULL || ft_strcmp("~", c[1]) == 0)
	{
		i = find_ev(shell->evs, "HOME=");
		chdir(&((shell->evs)[i][5]));
		return (set_new_pwd(shell, find_ev(shell->evs, "OLDPWD="), old));
	}
	i = find_ev(shell->evs, "OLDPWD=");
	if (ft_strcmp(c[1], "-") == 0 && i != -1)
	{
		chdir(&((shell->evs)[i][7]));
		shell_pwd();
	}
	else if (ft_strcmp(c[1], "-") == 0 && i == -1)
		return (shell_previous_fail(old));
	else if (chdir(c[1]) != 0)
	{
		free(old);
		ft_printf("minishell: cd: %s: No such file or directory\n", c[1]);
		return (1);
	}
	return (set_new_pwd(shell, i, old));
}

int	shell_cd(char **c, t_shell *shell)
{
	char	**newcmd;

	if (ft_strcmp(c[0], ".") == 0)
		return (0);
	if (ft_strcmp(c[0], "..") == 0)
	{
		newcmd = (char **)malloc(sizeof(char *) * 3);
		newcmd[0] = ft_strdup("cd");
		newcmd[1] = ft_strdup("..");
		newcmd[2] = NULL;
		shell_cd_do(newcmd, shell);
		free_array(newcmd);
		return (0);
	}
	else
		return (shell_cd_do(c, shell));
}
