/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   translate_envs.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/24 16:04:08 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/10/21 10:54:10 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*insert_rv(char *rv, char *arg)
{
	int		i;
	int		j;
	char	*new;
	char	*temp;

	i = 0;
	new = (char *)malloc(sizeof(ft_strlen(arg)));
	while (!(arg[i] == '$' && arg[i + 1] == '?'))
		i++;
	j = -1;
	while (j++ < i - 1)
		new[j] = arg[j];
	temp = new;
	new = ft_strjoin(new, rv);
	free(temp);
	free(rv);
	i += 2;
	if (arg[i] != '\0')
	{
		temp = new;
		new = ft_strjoin(new, &arg[i]);
		free(temp);
	}
	free(arg);
	return (new);
}

size_t	ft_evlen(char *ev)
{
	int	i;

	i = 0;
	while (ev[i] != '=')
		i++;
	return (i);
}

char	**insert_arg(char **args, char *new, int pos)
{
	int 	i;
	char	**newargs;

	i = 0;
	while (args[i] != NULL)
		i++;
	newargs = (char **)malloc(sizeof(char *) * i + 1);
	i = 0;
	while (i <= pos)
	{
		newargs[i] = ft_strdup(args[i]);
		i++;
	}
	newargs[i] = ft_strdup(new);
	free(new);
	while (args[i])
	{		
		newargs[i] = ft_strdup(args[i - 1]);
		i++;
	}
	newargs[i] = NULL;
	free_array(args);
	return (newargs);
}

int	check_env_space(char **args, int p)
{
	int		i;
	int		j;
	char	*temp;
	char	*old;

	i = 0;
	old = NULL;
	while (args[p][i] && !(args[p][i] == ' ' || args[p][i] == '\t'))
		i++;
	j = i;
	while (args[p][i] == ' ' || args[p][i] == '\t')
		i++;
	if (args[p][i])
	{
		// for (int k = 0; args[k]; k++)
		// 	printf("%i : %s\n", k, args[k]);
		temp = ft_strdup(&args[p][i]);
		printf("temp dupped, temp is %s\n", temp);
		ft_strlcpy(old, args[p], j);
		old = (char *)malloc(sizeof(char) * i + 1);
		printf("strlcpy done, old is %s\n", old);
		free(args[p]);
		args[p] = ft_strdup(old);
		printf("args[p] dupped, arg is %s\n", args[p]);
		args = insert_arg(args, temp, p);
		// for (int k = 0; args[k]; k++)
		// 	printf("%i : %s\n", k, args[k]);
		return (1);
	}
	return (0);
}

static char	*swap_env(char **args, int p, char **evs)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (evs[i])
	{
		j = 0;
		if (ft_strncmp(evs[i], &args[p][1], ft_evlen(evs[i])) == 0)
		{
			while (evs[i][j] != '=')
				j++;
			j++;
			temp = args[p];
			args[p] = ft_strdup(&evs[i][j]);
			free(temp);
		}
		i++;
	}
	while (1)
	{
		if (check_env_space(args, p) == 0)
			break;
	}
	return (args[p]);
}

static int	escapecheck(char *arg, int dollar)
{
	if (dollar == 0)
		return (0);
	if (ft_strncmp(&arg[dollar - 1], "\\$", 2) == 0)
		return (1);
	return (0);
}

static char	*remove_backslash(char *arg)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	new = (char *)malloc(sizeof(ft_strlen(arg)));
	if (new == NULL)
		return (NULL);
	while (arg[i])
	{
		if (!(arg[i] == '\\' && arg[i + 1] == '$'))
		{
			new[j] = arg[i];
			j++;
		}
		i++;
	}
	new[j] = '\0';
	free(arg);
	return (new);
}

static char	*choose_expansion(char **args, t_shell *shell, int i, int j)
{
	if (args[i][j + 1] == '?')
		return (insert_rv(ft_itoa(shell->rv), args[i]));
	else
		return (swap_env(args, i, shell->evs));
}

char	**expand_commands(t_shell *shell, char **args)
{
	int	i;
	int	j;

	i = 0;
	while (args && args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (args[i][j] == '$')
			{
				if (escapecheck(args[i], j) == 1)
					args[i] = remove_backslash(args[i]);
				else
				{
					args[i] = choose_expansion(args, shell, i, j);
					j = 0;
				}
			}
			j++;
		}
		i++;
	}
	return (args);
}
