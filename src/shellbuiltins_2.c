/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shellbuiltins_2.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/24 10:05:56 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/09/25 17:31:09 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** This is echo. It prints all arguments back with one space in between and a
** newline at the end, except for when the -n flag is given.
*/

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

/*
** This is a recreation of cat. It opens the target argument and
** reads and prints the contents, line by line.
*/

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
	close(fd);
	return (0);
}

char	**sort_alpha(char **evs)
{
	char 	**new;
	char	*temp;
	int 	i;
	int		j;

	new = copy_evs(evs);
	i = 0;
	temp = NULL;
	while (new[i] != NULL && i < j - 1)
	{
		j = i + 1;
		while (new[j] != NULL)
		{
			if (ft_strncmp(new[i], new[j], (ft_strlen(new[i]) > ft_strlen(new[j])
				? ft_strlen(new[i]) : ft_strlen(new[j]))) > 0)
			{
				temp = new[i];
				new[i] = new[j];
				new[j] = temp;
			}	
			j++;
		}
		i++;
	}
	return (new);
}


int		shell_export(char **args, char **evs)
{
	char **temp;

	temp = sort_alpha(evs);
	shell_env(args, temp);
	free_args(temp);
	return (0);
}
