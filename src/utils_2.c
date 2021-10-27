/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_env.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/27 14:10:12 by nkuipers      #+#    #+#                 */
/*   Updated: 2021/10/27 14:32:30 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**paths_without_path(char **commands)
{
	char	**paths;

	paths = (char **)malloc(sizeof(char *) * 2);
	paths[0] = ft_strdup(commands[0]);
	paths[1] = NULL;
	return (paths);
}

char	**set_new_env(char **evs, char *arg)
{
	int		i;
	char	**ret;

	i = 0;
	while (evs[i])
		i++;
	ret = malloc((i + 2) * (sizeof(char *)));
	if (!ret)
		return (NULL);
	i = 0;
	while (evs[i])
	{
		ret[i] = ft_strdup(evs[i]);
		i++;
	}
	if (ft_strchr(arg, '=') != NULL || ft_strcmp("/", arg) == 0)
		ret[i] = ft_strdup(arg);
	else
		ret[i] = ft_strjoin(arg, "=''");
	i++;
	ret[i] = NULL;
	free_array(evs);
	return (ret);
}

int	find_ev(char **evs, char *target)
{
	int		i;

	i = 0;
	while (evs[i] && ft_strncmp(evs[i], target, ft_strlen(target)) != 0)
		i++;
	if (evs[i] == NULL)
		return (-1);
	return (i);
}

int	is_type(t_token *token, int type)
{
	if (token && token->type == type)
		return (1);
	else
		return (0);
}

int	is_types(t_token *token, char *types)
{
	if (ft_strchr(types, ' ') && is_type(token, EMPTY))
		return (1);
	else if (ft_strchr(types, 'X') && is_type(token, CMD))
		return (1);
	else if (ft_strchr(types, 'x') && is_type(token, ARG))
		return (1);
	else if (ft_strchr(types, 'T') && is_type(token, TRUNC))
		return (1);
	else if (ft_strchr(types, 'A') && is_type(token, APPEND))
		return (1);
	else if (ft_strchr(types, 'I') && is_type(token, INPUT))
		return (1);
	else if (ft_strchr(types, 'P') && is_type(token, PIPE))
		return (1);
	else if (ft_strchr(types, 'E') && is_type(token, END))
		return (1);
	return (0);
}
