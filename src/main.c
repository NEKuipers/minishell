/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/21 21:22:15 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/09/23 15:39:38 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*shell_fnames[] =
{
	"cd",
	"pwd",
	"exit"
};

int		(*shell_functions[]) (char **, char **) =
{
	&shell_cd,
	&shell_pwd,
	&shell_exit
};

int		shell_pwd(char **args, char **evs)
{
	int i;

	i = 0;
	(void)args;
	while (ft_strncmp(evs[i], "PWD", 3) != 0)
		i++;
	ft_printf("%s\n", &evs[i][4]);
	return (0);
}

void	free_args(char **args)
{
	int i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	if (args)
		free(args);
}

int		shell_exit(char **args, char **evs)
{
	free_args(evs);
	free_args(args);
	ft_printf("Goodbye.\n");
	exit(0);
	return (0);
}

int		shell_cd(char **args, char **evs)
{
	(void)evs;
	if (!args[1])
		ft_printf("Please specify which directory you want to change to.\n");
	else
	{
		if (chdir(args[1]) != 0)
			ft_printf("That folder does not exist.\n");
	}
	return (0);
}

int		shell_execute(char **args, char **evs)
{
	unsigned long i;

	i = 0;
	while (i < (sizeof(shell_fnames) / sizeof(char *)))
	{
		if (ft_strncmp(args[0], shell_fnames[i], ft_strlen(args[0])) == 0)
			return (shell_functions[i](args, evs));
		i++;
	}
	ft_printf("That's not something I can do.\n");
	return (0);
}

void	shell_loop(char **evs)
{
	char *input;
	char **args;

	input = "";
	while (ft_strncmp(input, "exit", 5) != 0)
	{
		ft_printf("=> ");
		get_next_line(0, &input);
		args = ft_split(input, ' ');
		free(input);
		if (args[0] != NULL)
			shell_execute(args, evs);
		free_args(args);
	}
}

char	**copy_evs(char **inputs)
{
	int		i;
	char	**ret;

	i = 0;
	while (inputs[i])
		i++;
	ret = malloc((i + 1) * (sizeof(char *)));
	if (!ret)
		return (NULL);
	i = 0;
	while (inputs[i])
	{
		ret[i] = ft_strdup(inputs[i]);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

int		main(int argc, char **argv, char **envp)
{
	char **evs;

	evs = copy_evs(envp);
	if (evs == NULL)
		shell_exit(evs, evs);
	(void)argv;
	if (argc == 1)
	{
		ft_printf("Hi %s! Welcome to minishell. ", getenv("USER"));
		ft_printf("Enter 'exit' at any time to leave.\n");
		ft_printf("_______________________________________________________\n");
		shell_loop(evs);
	}
	return (0);
}
