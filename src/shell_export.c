/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_export.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/02 11:15:06 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/11/16 14:13:20 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Export: if no argument is supplied, all environment variables are printed
** in alphabetical order.
** If an argument with an = is supplied, such as TEST=NEW, a new environment
** variable is added following that scheme.
** If a different argument is supplied (i.e. export test), a new environment
** variable is added with no value (test='').
*/

static char	*envjoiner(char *dest, char *src)
{
	int		i;
	char	*sub;
	char	*temp;

	i = 0;
	while (src[i] != '=')
		i++;
	i++;
	sub = ft_substr(src, i, 2147483647);
	temp = dest;
	dest = ft_strjoin(temp, sub);
	free(temp);
	free(sub);
	return (dest);
}

static void	replace_env(t_shell *shell, char *arg, char op)
{
	int		index;
	char	*reform;

	index = match_env(shell->evs, arg);
	if (index >= 0)
	{
		if (op == '+')
			shell->evs[index] = envjoiner(shell->evs[index], arg);
		else if (ft_strchr(arg, '='))
		{
			free(shell->evs[index]);
			shell->evs[index] = ft_strdup(arg);
			if (ft_strlen(arg) > 0 && arg[ft_strlen(arg) - 1] == '=')
				shell->evs[index] = envjoiner(shell->evs[index], "=\'\'");
		}
	}
	else if (ft_strnstr(arg, "+=", (int)(ft_strchr(arg, '=') - arg) + 1))
	{
		reform = env_reform(arg);
		shell->evs = set_new_env(shell->evs, reform, 0);
		free(reform);
	}
	else
		shell->evs = set_new_env(shell->evs, arg, 0);
}

static void	empty_export(t_shell *shell)
{
	char	**temp[2];

	temp[0] = sort_alpha(shell->evs);
	temp[1] = shell->evs;
	shell->evs = temp[0];
	shell_env(shell);
	shell->evs = temp[1];
	free_array(temp[0]);
}

static int	envpluscheck(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '=' && i > 0)
		{
			if (arg[i - 1] == '+')
				return (1);
		}
		i++;
	}
	return (0);
}

int	shell_export(char **commands, t_shell *shell)
{
	int		i;
	int		rv;

	i = 1;
	rv = 0;
	while (commands[i] != NULL)
	{
		if (valid_identifier(commands[i], 1) == 1)
		{
			ft_printf("minishell: export: `%s': not a valid identifier\n", \
				commands[i]);
			rv = 1;
		}
		else if (envpluscheck(commands[i]) == 1)
			replace_env(shell, commands[i], '+');
		else
			replace_env(shell, commands[i], ' ');
		i++;
	}
	if (commands[1] == NULL)
		empty_export(shell);
	return (rv);
}
