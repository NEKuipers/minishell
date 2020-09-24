/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shellbuiltins_2.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/24 10:05:56 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/09/24 14:35:47 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		shell_echo(char **args, char **evs)
{
	int i;
	int	nflag;

	i = 1;
	nflag = 0;
	(void)evs;
	while (args[i])
	{
		if (ft_strncmp(args[i], "-n", 3) == 0)
		{
			i++;
			nflag = 1;
		}
		if (args[i] == NULL)
			return (0);
		else if (args[i + 1] == NULL && nflag == 0)
			ft_printf("%s\n", args[i]);
		else if (args[i + 1] == NULL)
			ft_printf("%s", args[i]);
		else
			ft_printf("%s ", args[i]);
		i++;
	}
	return (0);
}

int		shell_cat(char **args, char **evs)
{
	int		fd;
	char	*line;

	(void)evs;
	fd = open(args[1], O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		ft_printf("%s\n", line);
		if (line)
			free(line);
	}
	return (0);
}
